//
//  ViewController.m
//  MovieousPlayerDemo
//
//  Created by Chris Wang on 2018/8/14.
//  Copyright © 2018 Movieous Team. All rights reserved.
//

#import "ViewController.h"
#import <MovieousPlayer/MovieousPlayer.h>
#import <Reachability/Reachability.h>
#import <AVFoundation/AVFoundation.h>

@interface ViewController ()
<
MovieousPlayerControllerDelegate
>

@property (strong, nonatomic) IBOutlet UILabel *currentURLLabel;
@property (strong, nonatomic) IBOutlet UIButton *playButton;
@property (strong, nonatomic) IBOutlet UISlider *volumeSlider;
@property (strong, nonatomic) IBOutlet UISlider *seekSlider;
@property (strong, nonatomic) IBOutlet UITextView *URLInputTextView;
@property (strong, nonatomic) MovieousPlayerController *player;
@property (assign, nonatomic) BOOL isSeeking;
@property (strong, nonatomic) IBOutlet UIView *URLWindow;
@property (strong, nonatomic) NSMutableArray<NSURL *> *URLList;
@property (assign, nonatomic) NSUInteger currentURLIndex;
@property (strong, nonatomic) Reachability *reach;
@property (assign, nonatomic) NetworkStatus lastStatus;

@end

@implementation ViewController {
    NSTimer *_refreshTimer;
}

- (void)viewDidLoad {
    [super viewDidLoad];
#ifdef DEBUG
    MovieousPlayerController.logLevel = MPLogLevelError;
#else
    MovieousPlayerController.logLevel = MPLogLevelError;
#endif
    _URLList = [NSMutableArray arrayWithObjects:
                [[NSBundle mainBundle] URLForResource:@"VRDemo" withExtension:@"m4v"],
                [NSURL URLWithString:@"rtmp://rtmp.play.fh6b.cn/play/28758982"],
                [NSURL URLWithString:@"http://stream1.hnntv.cn/lywsgq/sd/live.m3u8"],
                nil];
    _currentURLIndex = 0;
    _currentURLLabel.text = _URLList[_currentURLIndex].absoluteString;
    [self reloadPlayer:_URLList[_currentURLIndex]];
    [_playButton setTitle:@"播放" forState:UIControlStateNormal];
    [_playButton setTitle:@"暂停" forState:UIControlStateSelected];
    _playButton.selected = YES;
    _refreshTimer = [NSTimer scheduledTimerWithTimeInterval:0.1 target:self selector:@selector(refreshTimerFired:) userInfo:nil repeats:YES];
    _reach = [Reachability reachabilityWithHostname:@"www.google.com"];
    _lastStatus = [_reach currentReachabilityStatus];
    [_reach startNotifier];
    NSError *error;
    if (![[AVAudioSession sharedInstance] setCategory:AVAudioSessionCategoryPlayback error:&error]) {
        @throw [NSException exceptionWithName:@"AVAudioSession setCategory failed" reason:[NSString stringWithFormat:@"%@", error] userInfo:nil];
    }
    [[NSNotificationCenter defaultCenter] addObserver:self
                                             selector:@selector(reachabilityChanged:)
                                                 name:kReachabilityChangedNotification
                                               object:nil];
}

- (void)refreshTimerFired:(NSTimer *)timer {
    if (_isSeeking) {
        return;
    }
    if (_player.totalDuration == 0) {
        _seekSlider.value = 0;
        return;
    }
    _seekSlider.value = _player.currentTime / _player.totalDuration;
}

- (void)reloadPlayer:(NSURL *)URL {
    [_player.playerView removeFromSuperview];
    MovieousPlayerOptions *options = [MovieousPlayerOptions defaultOptions];
    options.liveStreaming = YES;
    options.allowMixAudioWithOthers = NO;
    options.decoderType = MovieousPlayerDecoderTypeHardware;
    _player = [MovieousPlayerController playerControllerWithURL:URL options:options];
    _player.scalingMode = MPScalingModeAspectFit;
    _player.delegate = self;
    _player.interruptInBackground = NO;
    _player.VRMode = YES;
    _player.gyroscopeEnabled = YES;
    _player.touchToMoveEnabled = YES;
    _player.interruptionOperation = MPInterruptionOperationStop;
    _player.playerView.translatesAutoresizingMaskIntoConstraints = NO;
    [self.view insertSubview:_player.playerView atIndex:0];
    [NSLayoutConstraint activateConstraints:@[
                                              [NSLayoutConstraint constraintWithItem:_player.playerView attribute:NSLayoutAttributeTop relatedBy:NSLayoutRelationEqual toItem:self.view attribute:NSLayoutAttributeTop multiplier:1 constant:0],
                                              [NSLayoutConstraint constraintWithItem:_player.playerView attribute:NSLayoutAttributeLeft relatedBy:NSLayoutRelationEqual toItem:self.view attribute:NSLayoutAttributeLeft multiplier:1 constant:0],
                                              [NSLayoutConstraint constraintWithItem:_player.playerView attribute:NSLayoutAttributeBottom relatedBy:NSLayoutRelationEqual toItem:self.view attribute:NSLayoutAttributeBottom multiplier:1 constant:0],
                                              [NSLayoutConstraint constraintWithItem:_player.playerView attribute:NSLayoutAttributeRight relatedBy:NSLayoutRelationEqual toItem:self.view attribute:NSLayoutAttributeRight multiplier:1 constant:0],
                                              ]];
    [_player prepareToPlay];
    [_player play];
    _volumeSlider.value = _player.volume;
}

- (void)didReceiveMemoryWarning {
    NSLog(@"didReceiveMemoryWarning");
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)movieousPlayerController:(MovieousPlayerController *)playerController playStateDidChange:(MPPlayerState)playState {
    switch (playState) {
        case MPPlayerStateIdle:
        case MPPlayerStatePaused:
        case MPPlayerStateCompleted:
        case MPPlayerStateStopped:
        case MPPlayerStateError:
            _playButton.selected = NO;
            break;
        default:
            _playButton.selected = YES;
            break;
    }
    NSLog(@"playState changed to %ld", (long)playState);
}

- (BOOL)movieousPlayerController:(MovieousPlayerController *)playerController playerBeginsToRetry:(NSUInteger)currentCount {
    NSLog(@"playerBeginsToRetry: %lu", (unsigned long)currentCount);
    return YES;
}

- (void)movieousPlayerController:(MovieousPlayerController *)playerController playFinished:(MPFinishReason)finishReason {
    dispatch_async(dispatch_get_main_queue(), ^{
        self->_playButton.selected = NO;
    });
    NSLog(@"play finished because of %lu", (unsigned long)finishReason);
}

- (void)movieousPlayerControllerFirstVideoFrameRendered:(MovieousPlayerController *)playerController {
    NSLog(@"first video rendered");
}

- (void)movieousPlayerControllerFirstAudioFrameRendered:(MovieousPlayerController *)playerController {
    NSLog(@"first audio rendered");
}

- (IBAction)changeChannel:(UIButton *)sender {
    NSUInteger nextIndex = _currentURLIndex + 1;
    if (nextIndex >= _URLList.count) {
        nextIndex = 0;
    }
    _currentURLIndex = nextIndex;
    _currentURLLabel.text = _URLList[_currentURLIndex].absoluteString;
    [self reloadPlayer:_URLList[_currentURLIndex]];
}

- (IBAction)inputURLPressed:(UIButton *)sender {
    self.URLWindow.hidden = NO;
}

- (IBAction)volumeSliderChanged:(UISlider *)sender {
    _player.volume = sender.value;
}

- (IBAction)playButtonPressed:(UIButton *)sender {
    if (sender.selected) {
        [_player pause];
    } else {
        [_player play];
    }
}

- (IBAction)stopButtonPressed:(UIButton *)sender {
    [_player stop];
    _playButton.selected = NO;
}

- (IBAction)beginSeeking:(UISlider *)sender {
    _isSeeking = YES;
}

- (IBAction)endSeeking:(UISlider *)sender {
    _isSeeking = NO;
    _player.currentTime = _player.totalDuration * sender.value;
}

- (IBAction)completeInputURL:(UIButton *)sender {
    [_URLList addObject:[NSURL URLWithString:self.URLInputTextView.text]];
    _currentURLIndex = _URLList.count - 1;
    [self reloadPlayer:_URLList[_currentURLIndex]];
    _currentURLLabel.text = _URLList[_currentURLIndex].absoluteString;
    self.URLWindow.hidden = YES;
    [self.URLInputTextView resignFirstResponder];
}

- (IBAction)cancelInputURL:(UIButton *)sender {
    self.URLWindow.hidden = YES;
    [self.URLInputTextView resignFirstResponder];
}

- (void)reachabilityChanged:(NSNotification *)notification {
    if (_lastStatus != [_reach currentReachabilityStatus]) {
        _lastStatus = [_reach currentReachabilityStatus];
        [self reloadPlayer:_URLList[_currentURLIndex]];
    }
}

@end
