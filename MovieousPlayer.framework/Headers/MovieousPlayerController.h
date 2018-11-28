//
//  MovieousPlayerController.h
//  MovieousPlayer
//
//  Created by Chris Wang on 2018/8/14.
//  Copyright © 2018 Movieous Team. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <MovieousPlayer/MovieousPlayerOptions.h>

/*!
 * Scaling mode of MovieousPlayer content
 */
typedef NS_ENUM(NSInteger, MPScalingMode) {
    /*!
     * Uniform scale until one dimension fits
     */
    MPScalingModeAspectFit,
    /*!
     * Uniform scale until the movie fills the visible bounds. One dimension may have clipped contents
     */
    MPScalingModeAspectFill,
    /*!
     * Non-uniform scale. Both render dimensions will exactly match the visible bounds
     */
    MPScalingModeFill
};

/*!
 * State of the MovieousPlayer
 */
typedef NS_ENUM(NSInteger, MPPlayerState) {
    MPPlayerStateIdle,
    MPPlayerStatePreparing,
    MPPlayerStatePrepared,
    MPPlayerStatePlaying,
    MPPlayerStateBuffering,
    MPPlayerStateSeeking,
    MPPlayerStatePaused,
    MPPlayerStateCompleted,
    MPPlayerStateStopped,
    MPPlayerStateError,
};

/*!
 * The reason why MovieousPlayer finishes
 */
typedef NS_ENUM(NSInteger, MPFinishReason) {
    /*!
     * MovieousPlayer finishes because of play ended, this state may only not appear when play live video
     */
    MPFinishReasonPlaybackEnded,
    /*!
     * MovieousPlayer finishes because of some error
     */
    MPFinishReasonPlaybackError,
    /*!
     * MovieousPlayer finishes because user stops it
     */
    MPFinishReasonUserExited
};

/*!
 * The level of log
 */
typedef NS_ENUM(NSInteger, MPLogLevel) {
    /*!
     *  Unknown log level
     */
    MPLogLevelUnknown,
    /*!
     * Default log level
     */
    MPLogLevelDefault,
    /*!
     * Verbose log level
     */
    MPLogLevelVerbose,
    /*!
     * Debug log level
     */
    MPLogLevelDebug,
    /*!
     * Info log level
     */
    MPLogLevelInfo,
    /*!
     * Warn log level
     */
    MPLogLevelWarn,
    /*!
     * Error log level
     */
    MPLogLevelError,
    /*!
     * Fatal log level
     */
    MPLogLevelFatal,
    /*!
     * Silent log level
     */
    MPLogLevelSilent
};

/*!
 * What to do when MovieousPlayer is interrupted by other audio source
 */
typedef NS_ENUM(NSInteger, MPInterruptionOperation) {
    /*!
     * Call -pause when interrupted by other audio source
     */
    MPInterruptionOperationPause,
    /*!
    * Call -stop when interrupted by other audio source
    */
    MPInterruptionOperationStop,
};

@class MovieousPlayerController;

@protocol MovieousPlayerControllerDelegate<NSObject>

@optional

/*!
 * Notify delegate that MovieousPlayerController's first video frame has already rendered
 * @param playerController The MovieousPlayerController whose calls the method
 */
- (void)movieousPlayerControllerFirstVideoFrameRendered:(MovieousPlayerController *)playerController;

/*!
 * Notify delegate that MovieousPlayerController's first audio frame has already rendered
 * @param playerController The MovieousPlayerController whose calls the method
 */
- (void)movieousPlayerControllerFirstAudioFrameRendered:(MovieousPlayerController *)playerController;

/*!
 * Notify delegate that MovieousPlayerController's state has changed
 * @param playerController The MovieousPlayerController whose state has changed
 * @param playState The new state of MovieousPlayerController
 */
- (void)movieousPlayerController:(MovieousPlayerController *)playerController playStateDidChange:(MPPlayerState)playState;

/*!
 * Notify delegate that MovieousPlayerController's state has changed
 * @param playerController The MovieousPlayerController whose state has changed
 * @param previousState The previous state of MovieousPlayerController
 * @param newState The new state of MovieousPlayerController
 */
- (void)movieousPlayerController:(MovieousPlayerController *)playerController playStateDidChangeWithPreviousState:(MPPlayerState)previousState newState:(MPPlayerState)newState;

- (BOOL)movieousPlayerController:(MovieousPlayerController *)playerController playerBeginsToRetry:(NSUInteger)currentCount;

/*!
 * Notify delegate that MovieousPlayerController has finished playing
 * @param playerController The MovieousPlayerController that has finished
 * @param finishReason The reason why MovieousPlayerController has finished
 */
- (void)movieousPlayerController:(MovieousPlayerController *)playerController playFinished:(MPFinishReason)finishReason;

@end

@interface MovieousPlayerController : NSObject

/*!
 * The global log level
 */
@property (nonatomic, assign, class) MPLogLevel logLevel;

/*!
 * Options which initialize the controller
 */
@property (nonatomic, strong, readonly) MovieousPlayerOptions *options;

/*!
 * This view displays visual content of the video
 */
@property (nonatomic, readonly) UIView *playerView;

/*!
 * Total duration of the video you are playing
 */
@property (nonatomic, readonly) NSTimeInterval totalDuration;

/*!
 * State of the controller
 */
@property (nonatomic, readonly) MPPlayerState playState;

/*!
 * Size of the video you are playing
 */
@property (nonatomic, readonly) CGSize naturalSize;

/*!
 * Take a snapshot of the current scene
 * @return The snapshot captured
 */
@property (nonatomic, readonly) UIImage *snapshot;

/*!
 * Current time in the time range of your video
 */
@property (nonatomic, assign) NSTimeInterval currentTime;

/*!
 * How to scale content when aspect ratios of the content and preview are not equal
 * Default to MPScalingModeNone
 */
@property (nonatomic, assign) MPScalingMode scalingMode;

/*!
 * Volume of the player
 * Default to 1
 */
@property (nonatomic, assign) float volume;

/*!
 * Whether to pause when enter background, you should set this property to NO when you want to keep playing in background
 * Default to YES
 */
@property (nonatomic, assign) BOOL pauseInBackground DEPRECATED_ATTRIBUTE;

/*!
 * Whether to get interrupted when enter background, you should set this property to NO when you want to keep playing in background
 * Default to YES
 */
@property (nonatomic, assign) BOOL interruptInBackground;

/*!
 * What to do when interrupted by other audio source
 * Default to MPInterruptionOperationPause
 */
@property (nonatomic, assign) MPInterruptionOperation interruptionOperation;

/*!
 * Retry playing when error occurs
 * Default to YES
 */
@property (nonatomic, assign) BOOL retryIfError;

/*!
 * Delegate of the player controller
 */
@property (nonatomic, weak) id<MovieousPlayerControllerDelegate> delegate;

/*!
 * Whether to loop when play completed
 */
@property (nonatomic, assign) BOOL loop;

/*!
 * Is VRMode Enabled
 */
@property (nonatomic, assign) BOOL VRMode;

/*!
 * Is gyroscope Enabled, only valid when VRMode is ON
 */
@property (nonatomic,assign) BOOL gyroscopeEnabled;

/*!
 * Is dualScreen Enabled, only valid when VRMode is ON
 */
@property (nonatomic, assign) BOOL dualScreen;

/*!
 * Is touch to move Enabled, only valid when VRMode is ON
 */
@property (nonatomic, assign) BOOL touchToMoveEnabled;

/*!
 *
 * @param URL The URL of URL you want to play
 * @return The initialized playerController
 */
+ (instancetype)playerControllerWithURL:(NSURL *)URL;

/*!
 *
 * @param URL The URL of URL you want to play
 * @param options The options to use
 * @return The initialized playerController
 */
+ (instancetype)playerControllerWithURL:(NSURL *)URL options:(MovieousPlayerOptions *)options;

/*!
 *
 * @param URL The URL of URL you want to play
 * @return The initialized playerController
 */
- (instancetype)initWithURL:(NSURL *)URL;

/*!
 *
 * @param URL The URL of URL you want to play
 * @param options The options to use
 * @return The initialized playerController
 */
- (instancetype)initWithURL:(NSURL *)URL options:(MovieousPlayerOptions *)options;

/*!
 * prepareToPlay
 */
- (void)prepareToPlay;

/*!
 * Play
 */
- (void)play;

/*!
 * Pause
 */
- (void)pause;

/*!
 * Stop
 */
- (void)stop;

@end
