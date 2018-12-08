//
//  MovieousPlayerController.h
//  MovieousPlayer
//
//  Created by Chris Wang on 2018/8/14.
//  Copyright © 2018 Movieous Team. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <MovieousPlayer/MovieousPlayerOptions.h>

/**
 * @brief Scaling mode of MovieousPlayer content
 */
typedef NS_ENUM(NSInteger, MPScalingMode) {
    /**
     * @brief Uniform scale until one dimension fits
     */
    MPScalingModeAspectFit,
    /**
     * @brief Uniform scale until the movie fills the visible bounds. One dimension may have clipped contents
     */
    MPScalingModeAspectFill,
    /**
     * @brief Non-uniform scale. Both render dimensions will exactly match the visible bounds
     */
    MPScalingModeFill
};

/**
 * @brief State of the MovieousPlayer
 */
typedef NS_ENUM(NSInteger, MPPlayerState) {
    /**
     * @brief State of fresh initialized player
     */
    MPPlayerStateIdle,
    /**
     * @brief Preparing to play
     */
    MPPlayerStatePreparing,
    /**
     * @brief Prepared to play
     */
    MPPlayerStatePrepared,
    /**
     * @brief Player is now playing
     */
    MPPlayerStatePlaying,
    /**
     * @brief Player is now buffering due to slow network connection
     */
    MPPlayerStateBuffering,
    /**
     * @brief Player is now seeking to a new place
     */
    MPPlayerStateSeeking,
    /**
     * @brief Player is paused
     */
    MPPlayerStatePaused,
    /**
     * @brief Play of current media source has completed
     */
    MPPlayerStateCompleted,
    /**
     * @brief Player has stopped, Player will turn to this state after -stop is called
     */
    MPPlayerStateStopped,
    /**
     * @brief Some error has occured
     */
    MPPlayerStateError,
};

/**
 * @brief The reason why MovieousPlayer finishes
 */
typedef NS_ENUM(NSInteger, MPFinishReason) {
    /**
     * @brief MovieousPlayer finishes because of play ended, this state may only not appear when play live video
     */
    MPFinishReasonPlaybackEnded,
    /**
     * @brief MovieousPlayer finishes because of some error
     */
    MPFinishReasonPlaybackError,
    /**
     * @brief MovieousPlayer finishes because user stops it
     */
    MPFinishReasonUserExited
};

/**
 * @brief The level of log
 */
typedef NS_ENUM(NSInteger, MPLogLevel) {
    /**
     * @brief Unknown log level
     */
    MPLogLevelUnknown,
    /**
     * @brief Default log level
     */
    MPLogLevelDefault,
    /**
     * @brief Verbose log level
     */
    MPLogLevelVerbose,
    /**
     * @brief Debug log level
     */
    MPLogLevelDebug,
    /**
     * @brief Info log level
     */
    MPLogLevelInfo,
    /**
     * @brief Warn log level
     */
    MPLogLevelWarn,
    /**
     * @brief Error log level
     */
    MPLogLevelError,
    /**
     * @brief Fatal log level
     */
    MPLogLevelFatal,
    /**
     * @brief Silent log level
     */
    MPLogLevelSilent
};

/**
 * @brief What to do when MovieousPlayer is interrupted by other audio source
 */
typedef NS_ENUM(NSInteger, MPInterruptionOperation) {
    /**
     * @brief Call -pause when interrupted by other audio source
     */
    MPInterruptionOperationPause,
    /**
    * @brief Call -stop when interrupted by other audio source
    */
    MPInterruptionOperationStop,
};

@class MovieousPlayerController;

@protocol MovieousPlayerControllerDelegate<NSObject>

@optional

/**
 * @brief Notify delegate that MovieousPlayerController's first video frame has already rendered
 * @param playerController The MovieousPlayerController whose calls the method
 */
- (void)movieousPlayerControllerFirstVideoFrameRendered:(MovieousPlayerController *)playerController;

/**
 * @brief Notify delegate that MovieousPlayerController's first audio frame has already rendered
 * @param playerController The MovieousPlayerController whose calls the method
 */
- (void)movieousPlayerControllerFirstAudioFrameRendered:(MovieousPlayerController *)playerController;

/**
 * @brief Notify delegate that MovieousPlayerController's state has changed
 * @param playerController The MovieousPlayerController whose state has changed
 * @param playState The new state of MovieousPlayerController
 */
- (void)movieousPlayerController:(MovieousPlayerController *)playerController playStateDidChange:(MPPlayerState)playState;

/**
 * @brief Notify delegate that MovieousPlayerController's state has changed
 * @param playerController The MovieousPlayerController whose state has changed
 * @param previousState The previous state of MovieousPlayerController
 * @param newState The new state of MovieousPlayerController
 */
- (void)movieousPlayerController:(MovieousPlayerController *)playerController playStateDidChangeWithPreviousState:(MPPlayerState)previousState newState:(MPPlayerState)newState;

/**
 * @brief Notify delegate that MovieousPlayerController's has begun to retry reconnecting
 * @param playerController The MovieousPlayerController trying to reconnect
 * @param currentCount Current retried count
 */
- (BOOL)movieousPlayerController:(MovieousPlayerController *)playerController playerBeginsToRetry:(NSUInteger)currentCount;

/**
 * @brief Notify delegate that MovieousPlayerController has finished playing
 * @param playerController The MovieousPlayerController that has finished
 * @param finishReason The reason why MovieousPlayerController has finished
 */
- (void)movieousPlayerController:(MovieousPlayerController *)playerController playFinished:(MPFinishReason)finishReason;

@end

@interface MovieousPlayerController : NSObject

/**
 * @brief The global log level
 */
@property (nonatomic, assign, class) MPLogLevel logLevel;

/**
 * @brief Options which initialize the controller
 */
@property (nonatomic, strong, readonly) MovieousPlayerOptions *options;

/**
 * @brief This view displays visual content of the video
 */
@property (nonatomic, readonly) UIView *playerView;

/**
 * @brief Total duration of the video you are playing
 */
@property (nonatomic, readonly) NSTimeInterval totalDuration;

/**
 * @brief State of the controller
 */
@property (nonatomic, readonly) MPPlayerState playState;

/**
 * @brief Size of the video you are playing
 */
@property (nonatomic, readonly) CGSize naturalSize;

/**
 * @brief Take a snapshot of the current scene
 * @return The snapshot captured
 */
@property (nonatomic, readonly) UIImage *snapshot;

/**
 * @brief Current time in the time range of your video
 */
@property (nonatomic, assign) NSTimeInterval currentTime;

/**
 * @brief How to scale content when aspect ratios of the content and preview are not equal
 * Default to MPScalingModeNone
 */
@property (nonatomic, assign) MPScalingMode scalingMode;

/**
 * @brief Volume of the player
 * Default to 1
 */
@property (nonatomic, assign) float volume;

/**
 * @brief Whether to pause when enter background, you should set this property to NO when you want to keep playing in background
 * Default to YES
 */
@property (nonatomic, assign) BOOL pauseInBackground DEPRECATED_ATTRIBUTE;

/**
 * @brief Whether to get interrupted when enter background, you should set this property to NO when you want to keep playing in background
 * Default to YES
 */
@property (nonatomic, assign) BOOL interruptInBackground;

/**
 * @brief What to do when interrupted by other audio source
 * Default to MPInterruptionOperationPause
 */
@property (nonatomic, assign) MPInterruptionOperation interruptionOperation;

/**
 * @brief Retry playing when error occurs
 * Default to YES
 */
@property (nonatomic, assign) BOOL retryIfError;

/**
 * @brief Delegate of the player controller
 */
@property (nonatomic, weak) id<MovieousPlayerControllerDelegate> delegate;

/**
 * @brief Whether to loop when play completed
 */
@property (nonatomic, assign) BOOL loop;

/**
 * @brief Is VRMode enabled
 */
@property (nonatomic, assign) BOOL VRMode;

/**
 * @brief Is gyroscope enabled, only valid when VRMode is on
 */
@property (nonatomic,assign) BOOL gyroscopeEnabled;

/**
 * @brief Is dualScreen Enabled, only valid when VRMode is ON
 */
@property (nonatomic, assign) BOOL dualScreen;

/**
 * @brief Is touch to move Enabled, only valid when VRMode is ON
 */
@property (nonatomic, assign) BOOL touchToMoveEnabled;

/**
 * @brief Create a MovieousPlayerController instance with media URL
 * @param URL The URL of URL you want to play
 * @return The initialized playerController
 */
+ (instancetype)playerControllerWithURL:(NSURL *)URL;

/**
 * @brief Create a MovieousPlayerController instance with media URL and options
 * @param URL The URL of URL you want to play
 * @param options The options to use
 * @return The initialized playerController
 */
+ (instancetype)playerControllerWithURL:(NSURL *)URL options:(MovieousPlayerOptions *)options;

/**
 * @brief Initialize a MovieousPlayerController instance with media URL
 * @param URL The URL you want to play
 * @return The initialized playerController
 */
- (instancetype)initWithURL:(NSURL *)URL;

/**
 * @brief Initialize a MovieousPlayerController instance with media URL and options
 * @param URL The URL you want to play
 * @param options The options to use
 * @return The initialized playerController
 */
- (instancetype)initWithURL:(NSURL *)URL options:(MovieousPlayerOptions *)options;

/**
 * @brief prepareToPlay
 */
- (void)prepareToPlay;

/**
 * @brief Play
 */
- (void)play;

/**
 * @brief Pause
 */
- (void)pause;

/**
 * @brief Stop
 */
- (void)stop;

@end
