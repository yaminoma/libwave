
#import "LevelMeterView.h"


@implementation LevelMeterView

-(id)initWithFrame:(CGRect)frame
{
    self = [super initWithFrame:frame];
    
    m_peakEnvBar = [[UIView alloc] init];
    m_peakEnvBar.backgroundColor = [UIColor greenColor];
    m_peakEnvBar.alpha = 0.2f;
    [self addSubview:m_peakEnvBar];
    
    m_peakLine = [[UIView alloc] init];
    m_peakLine.backgroundColor = [UIColor greenColor];
    m_peakLine.alpha = 1.0f;
    [self addSubview:m_peakLine];
    
    m_rmsLine = [[UIView alloc] init];
    m_rmsLine.backgroundColor = [UIColor yellowColor];
    m_rmsLine.alpha = 0.6f;
    [self addSubview:m_rmsLine];
    
    m_clipIndicator = [[UIView alloc] init];
    m_clipIndicator.backgroundColor = [UIColor redColor];
    m_clipIndicator.alpha = 0.0f;
    [self addSubview:m_clipIndicator];
    
    return self;
}

-(void)layoutSubviews
{
    [self updateInfo:&m_currentInfo];
}

-(void)updateInfo:(WaveRealtimeInfo*)info
{
    memcpy(&m_currentInfo, info, sizeof(WaveRealtimeInfo));
    
    //printf("recorded time: %f\n", info->numRecordedSeconds);
    
    const int w = self.frame.size.width;
    const int h = self.frame.size.height;
    const int lw = 4;
    
    m_rmsLine.frame = CGRectMake((int)((w - lw) * m_currentInfo.rmsLevel),
                                 0,
                                 lw,
                                 h);
    
    m_peakLine.frame = CGRectMake((int)((w - lw) * m_currentInfo.peakLevel),
                                 0,
                                 lw,
                                 h);
    
    m_peakEnvBar.frame = CGRectMake(0, 0, (int)(w * m_currentInfo.peakLevelEnvelope), h);
    
    m_clipIndicator.frame = CGRectMake(w - lw, 0, lw, h);
    if (m_currentInfo.hasClipped)
    {
        m_clipIndicator.alpha = 1.0f;
        [UIView animateWithDuration:4.0f animations:^(void) {
            m_clipIndicator.alpha = 0.0f;
        }];
    }
}

@end
