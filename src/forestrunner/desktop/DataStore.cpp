/*
 *  Copyright (C) 2012 Josh Bialkowski (jbialk@mit.edu)
 *
 *  This file is part of forestrunner.
 *
 *  forestrunner is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  forestrunner is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Fontconfigmm.  If not, see <http://www.gnu.org/licenses/>.
 */
/**
 *  \file   DataStore.cpp
 *
 *  \date   Aug 30, 2012
 *  \author Josh Bialkowski (jbialk@mit.edu)
 *  \brief  
 */

#include "forestrunner/desktop/DataStore.h"
#include "app/linux.h"

#include <boost/filesystem.hpp>
#include <cstdlib>
#include <cstring>
#include <Ogre.h>
#include <soci/sqlite3/soci-sqlite3.h>

#ifndef FORESTRUNNER_WINDOWS
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#endif


#ifdef FORESTRUNNER_OSX
#include <pwd.h>
#include <unistd.h>
#include <iOS/macUtils.h>
#endif

#ifdef FORESTRUNNER_IOS
#include <iOS/macUtils.h>
#endif

namespace forestrunner {
namespace      desktop {



DataStore::DataStore()
{


#ifdef FORESTRUNNER_LINUX
    m_dataDir       = std::string(getenv("HOME")) + "/.forestrunner";
    m_resourceDir   = std::string(g_installPrefix) + "/share/forestrunner";
#elif FORESTRUNNER_WINDOWS
    m_dataDir = std::string(getenv("APPDATA")) + "/forestrunner";
    m_resourceDir = ""; // FIXME: need resource location for windows
#elif FORESTRUNNER_OSX
    const struct passwd* pwd = getpwuid(getuid());
    m_dataDir = std::string(pwd->pw_dir) + "/.forestrunner";
    m_resourceDir = Ogre::macBundlePath() + "/Contents/Resources";
#elif FORESTRUNNER_IOS
    m_dataDir = Ogre::macBundlePath() + "/../Documents/";
    m_resourceDir = Ogre::macBundlePath() + "/resources";
#endif

}


void DataStore::run_init_script()
{
// we can't use mmap on windows
#ifndef FORESTRUNNER_WINDOWS
    // open the file
        std::string path = m_resourceDir + "/Initialize.sql";
        int fd = open( path.c_str(), O_RDONLY );
        if( fd < 0 )
        {
            std::cerr << "Failed to open file: "
                      << path
                      << "\n   error: " << std::strerror(errno)
                      << std::endl;
            return;
        }

        // stat the file to get it's size
        struct stat fs;
        int result = fstat(fd,&fs);
        if( result < 0 )
        {
            std::cerr << "Failed to open file: "
                      << path
                      << "\n   error: " << std::strerror(errno)
                      << std::endl;
            close(fd);
            return;
        }

        // map the file into memory
        // offset for mmap must be page aligned ??
        // off_t offset = fs.st_size & ~( sysconf(_SC_PAGE_SIZE) -1);
        off_t  offset       = 0;
        size_t mapLength    = fs.st_size;

        // note that MAP_PRIVATE means copy on write and do not change the
        // underlying file
        void *mapAddr = mmap( NULL, mapLength,
                            PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, offset );
        if( mapAddr == MAP_FAILED )
        {
            std::cerr << "Failed to map file: "
                      << path
                      << "\n   error: " << std::strerror(errno)
                      << std::endl;
            close(fd);
            return;
        }


        // now get a char pointer and search for all the ';' chars, everything
        // before a ';' is a command that soci needs to execute;
        char* start = (char*)mapAddr;

        // null terminate the file
        *(start + mapLength) = '\0';

        // get the first token
        char* tok = strtok(start, ";");

        std::cout << "Initializing database\n--------------\n";
        while(tok)
        {
            // replace newlines with spaces
            for( char* nl = strchr(tok,'\n'); nl != NULL; nl = strchr(nl,'\n') )
                *nl = ' ';

            // pass the command to soci
            std::cout << tok << "\n";
            m_soci << tok;

            // find the next command
            tok = strtok(NULL,";");
        }
        std::cout << std::endl;


        // now that we're done, unmap and close the file
        munmap(mapAddr,mapLength);
        close(fd);
#endif
}

void DataStore::read_properties()
{
    std::cout << "Reading properties from store:\n-----------------------\n";

    typedef datastore::Map_t::iterator Iterator_t;
    for( Iterator_t iPair = m_map.begin(); iPair != m_map.end(); iPair++)
    {
        switch( iPair->second->type() )
        {
            case datastore::BOOL:
            {
                int val;
                m_soci << "SELECT bool_value "
                            "FROM booleans "
                                "WHERE bool_key='"
                            << keystr(iPair->first)
                            << "'",
                            soci::into(val);
                iPair->second->get<bool>() = val;
                break;
            }

            case datastore::INT:
            {
                m_soci << "SELECT int_value "
                            "FROM integers "
                                "WHERE int_key='"
                            << keystr(iPair->first)
                            << "'",
                            soci::into(iPair->second->get<int>());
                break;
            }

            case datastore::STRING:
            {
                std::string val;
                m_soci << "SELECT string_value "
                            "FROM strings "
                                "WHERE string_key='"
                            << keystr(iPair->first)
                            << "'",
                            soci::into(val);
                iPair->second->get<std::string>() = val;
                break;
            }

            default:
            {
                std::cerr << "FIXME: unknown key type stored in property map"
                          << std::endl;
                break;
            }
        }

        std::cout << "   " << keystr(iPair->first) << " : " << *(iPair->second) << "\n";
    }
    std::cout << std::endl;
}


void DataStore::init()
{
    using namespace soci;
    namespace fs = boost::filesystem;
    try
    {
        fs::path dbPath(m_dataDir + "/store.sqlite");
        bool dbExistsAlready = fs::exists(dbPath);
        m_soci.open( sqlite3, m_dataDir + "/store.sqlite");
        if( !dbExistsAlready )
            run_init_script();

        read_properties();
    }
    catch( std::exception const &e)
    {
        std::cerr << "SOCI error: " << e.what() << std::endl;
    }

}

void DataStore::flush()
{
    std::cout << "Writing properties to store:\n-----------------------\n";

    typedef datastore::Map_t::iterator Iterator_t;
    for( Iterator_t iPair = m_map.begin(); iPair != m_map.end(); iPair++)
    {
        switch( iPair->second->type() )
        {
            case datastore::BOOL:
            {
                int val = iPair->second->get<bool>() ? 1 : 0;
                m_soci << "UPDATE booleans "
                            "SET bool_value= " << val << " "
                            "WHERE bool_key='"
                            << keystr(iPair->first)
                            << "'";
                break;
            }

            case datastore::INT:
            {
                int val = iPair->second->get<int>();
                m_soci << "UPDATE integers "
                            "SET int_value=" << val << " "
                            "WHERE int_key='"
                            << keystr(iPair->first)
                            << "'";
                break;
            }

            case datastore::STRING:
            {
                std::string val = iPair->second->get<std::string>();
                m_soci << "UPDATE strings "
                            "SET string_value='" << val << "' "
                            "WHERE string_key='"
                            << keystr(iPair->first)
                            << "'";
                break;
            }

            default:
            {
                std::cerr << "FIXME: unknown key type stored in property map"
                          << std::endl;
                break;
            }
        }

        std::cout << "   " << keystr(iPair->first) << " : " << *(iPair->second) << "\n";
    }
    std::cout << std::endl;
}

void DataStore::write_score(double score){}

void DataStore::sync_scores(){}

void DataStore::fini()
{
    try
    {
        m_soci.close();
    }
    catch( std::exception const &e)
    {
        std::cerr << "SOCI error: " << e.what() << std::endl;
    }
}







} // namespace desktop 
} // namespace forestrunner 
