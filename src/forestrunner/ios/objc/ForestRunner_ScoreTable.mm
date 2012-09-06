//
//  ForestRunner_ScoreTable.m
//  forestrunner_ios
//
//  Created by Josh  Bialkowski on 9/6/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "ForestRunner_ScoreTable.h"
#import "ForestRunner_ScoreCell.h"
#include <ctime>
#include <forestrunner/util/Printf.hpp>

@interface ForestRunner_ScoreTable ()

@end

@implementation ForestRunner_ScoreTable

- (void) setDataStore:(forestrunner::DataStore *)store
{
    m_dataStore = store;
}

- (void) setScore:(float)score
{
    m_score = score;
}

- (id)initWithStyle:(UITableViewStyle)style
{
    self = [super initWithStyle:style];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];

    // Uncomment the following line to preserve selection between presentations.
    // self.clearsSelectionOnViewWillAppear = NO;
 
    // Uncomment the following line to display an Edit button in the navigation bar for this view controller.
    // self.navigationItem.rightBarButtonItem = self.editButtonItem;
}

- (void) viewWillAppear:(BOOL)animated
{
    m_dataStore->write_score(m_score);
    m_dataStore->sync_scores();
}

- (void) viewDidAppear:(BOOL)animated
{

}

- (void)viewDidUnload
{
    [super viewDidUnload];
    // Release any retained subviews of the main view.
    // e.g. self.myOutlet = nil;
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}



#pragma mark - Table view data source

- (NSInteger)numberOfSectionsInTableView:(UITableView *)tableView
{
    // Return the number of sections.
    return 2;
}

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    switch(section)
    {
        case 0:
            return m_dataStore->userScores().size();
            
        case 1:
            return m_dataStore->globalScores().size();
            
        default:
            return 0;
    }
}

- (UITableViewCell *)tableView:(UITableView *)tableView 
        cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    using namespace forestrunner::datastore;
    using namespace forestrunner::keys;

    static NSString *CellIdentifier = @"scoreCell";
    ForestRunner_ScoreCell *cell = [tableView 
                            dequeueReusableCellWithIdentifier:CellIdentifier];
    if (cell == nil) 
    {
        cell = [[ForestRunner_ScoreCell alloc]
          initWithStyle:UITableViewCellStyleDefault 
          reuseIdentifier:CellIdentifier];
    }
    
    int section = [indexPath section];
    int row     = [indexPath row    ];
    switch( section )
    {
        case 0:
        {
            const UserHighScoreRow& dRow 
                = m_dataStore->userScores()[row];
            strftime(m_dateBuf,63,"%m/%d %H:%M",localtime(&dRow.date));
                
            cell.label_nick.text = [NSString stringWithUTF8String: 
                        m_dataStore->get<std::string>(USERNAME).c_str()];
            cell.label_date.text = [NSString stringWithUTF8String: 
                        m_dateBuf ];
            cell.label_score.text = [NSString stringWithUTF8String: 
                        m_scoreBuf("%0.2f",dRow.score) ];
            break;
        }
            
        case 1:
        {
            const GlobalHighScoreRow& dRow 
                = m_dataStore->globalScores()[row];
            strftime(m_dateBuf,63,"%m/%d %H:%M",localtime(&dRow.date));
                
            cell.label_nick.text = [NSString stringWithUTF8String: 
                        dRow.username.c_str()];
            cell.label_date.text = [NSString stringWithUTF8String: 
                        m_dateBuf ];
            cell.label_score.text = [NSString stringWithUTF8String: 
                        m_scoreBuf("%0.2f",dRow.score) ];
            break;
        }
        
        default:
            break;
    }

    
    
    
    
    return cell;
}

/*
// Override to support conditional editing of the table view.
- (BOOL)tableView:(UITableView *)tableView canEditRowAtIndexPath:(NSIndexPath *)indexPath
{
    // Return NO if you do not want the specified item to be editable.
    return YES;
}
*/

/*
// Override to support editing the table view.
- (void)tableView:(UITableView *)tableView commitEditingStyle:(UITableViewCellEditingStyle)editingStyle forRowAtIndexPath:(NSIndexPath *)indexPath
{
    if (editingStyle == UITableViewCellEditingStyleDelete) {
        // Delete the row from the data source
        [tableView deleteRowsAtIndexPaths:[NSArray arrayWithObject:indexPath] withRowAnimation:UITableViewRowAnimationFade];
    }   
    else if (editingStyle == UITableViewCellEditingStyleInsert) {
        // Create a new instance of the appropriate class, insert it into the array, and add a new row to the table view
    }   
}
*/

/*
// Override to support rearranging the table view.
- (void)tableView:(UITableView *)tableView moveRowAtIndexPath:(NSIndexPath *)fromIndexPath toIndexPath:(NSIndexPath *)toIndexPath
{
}
*/

/*
// Override to support conditional rearranging of the table view.
- (BOOL)tableView:(UITableView *)tableView canMoveRowAtIndexPath:(NSIndexPath *)indexPath
{
    // Return NO if you do not want the item to be re-orderable.
    return YES;
}
*/

#pragma mark - Table view delegate

- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    // Navigation logic may go here. Create and push another view controller.
    /*
     <#DetailViewController#> *detailViewController = [[<#DetailViewController#> alloc] initWithNibName:@"<#Nib name#>" bundle:nil];
     // ...
     // Pass the selected object to the new view controller.
     [self.navigationController pushViewController:detailViewController animated:YES];
     [detailViewController release];
     */
}

@end
