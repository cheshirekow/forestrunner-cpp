DROP TABLE IF EXISTS strings;
DROP TABLE IF EXISTS booleans;
DROP TABLE IF EXISTS integers;
DROP TABLE IF EXISTS unsent_score;
DROP TABLE IF EXISTS user_data;
DROP TABLE IF EXISTS global_data;

CREATE TABLE strings (
    string_key      TEXT PRIMARY KEY, 
    string_value    TEXT
);

CREATE TABLE booleans (
    bool_key    TEXT PRIMARY KEY, 
    bool_value  BOOLEAN
);

CREATE TABLE integers (
    int_key        TEXT PRIMARY KEY,
    int_value      INTEGER
);

CREATE TABLE unsent_score(
    score_id        INTEGER PRIMARY KEY AUTOINCREMENT,
    date            INTEGER,
    velocity        INTEGER,
    density         INTEGER,
    radius          INTEGER,
    score           FLOAT
);

CREATE TABLE user_data (
    data_id         INTEGER PRIMARY KEY AUTOINCREMENT,
    date            INTEGER,
    velocity        INTEGER,
    density         INTEGER,
    radius          INTEGER,
    score           FLOAT
);

CREATE TABLE global_data (
    data_id         INTEGER PRIMARY KEY AUTOINCREMENT,
    nick            TEXT,
    date            INTEGER,
    velocity        INTEGER,
    density         INTEGER,
    radius          INTEGER,
    score           FLOAT,
    global_id       INTEGER
);

CREATE UNIQUE INDEX global_id_index ON global_data (global_id);

INSERT INTO strings
        SELECT 'hash'       , ''
 UNION  SELECT 'username'   , 'Anon';

INSERT INTO booleans  
        SELECT 'adv:participate'    , 1
 UNION  SELECT 'adv:postProcess'    , 0
 UNION  SELECT 'adv:fogFilter'      , 0 
 UNION  SELECT 'adv:cartoon'        , 1  
 UNION  SELECT 'adv:lighting'       , 0 
 UNION  SELECT 'adv:patchGrids'     , 0 
 UNION  SELECT 'adv:mainGrid'       , 1  
 UNION  SELECT 'adv:gradientFloor'  , 0 
 UNION  SELECT 'adv:logging'        , 0 
 UNION  SELECT 'adv:worldRotate'    , 1  ;

INSERT INTO integers
        SELECT 'pref:density',    1
 UNION  SELECT 'pref:radius' ,    1 
 UNION  SELECT 'pref:velocity'  , 1
 UNION  SELECT 'stat:version',    3;