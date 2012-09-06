//
//  ForestRunner_ScoreCell.m
//  forestrunner_ios
//
//  Created by Josh  Bialkowski on 9/6/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "ForestRunner_ScoreCell.h"

@implementation ForestRunner_ScoreCell

@synthesize label_nick;
@synthesize label_date;
@synthesize label_score;


- (id)initWithStyle:(UITableViewCellStyle)style reuseIdentifier:(NSString *)reuseIdentifier
{
    self = [super initWithStyle:style reuseIdentifier:reuseIdentifier];
    if (self) {
        // Initialization code
    }
    return self;
}

- (void)setSelected:(BOOL)selected animated:(BOOL)animated
{
    [super setSelected:selected animated:animated];

    // Configure the view for the selected state
}

@end
