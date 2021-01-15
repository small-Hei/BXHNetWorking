//
//  BXHHTTPSessionManager.h
//  AFNetworking
//
//  Created by baishuang on 2021/1/11.
//

typedef NS_ENUM(NSInteger, BXHHTTPRequestCacheType) {
    /**
     *  接口数据来自server
     */
    BXHHTTPRequestCacheTypeNone,
    /**
     *  接口数据来自内存缓存
     */
    BXHHTTPRequestCacheTypeMemory,
    /**
     *  接口数据来自磁盘缓存
     */
    BXHHTTPRequestCacheTypeDisk,
    /**
     *  接口数据来自磁盘/内存缓存，已过期，新数据会在下一次success回调中返回
     */
    BXHHTTPRequestCacheTypeExpired
};

@class BXHHTTPRequestConfig;

typedef void (^BXHHTTPRequestCacheHandler)(BXHHTTPRequestCacheType cacheType);
typedef void (^BXHHTTPRequestSuccessHandler)(id _Nullable response, BXHHTTPRequestCacheType cacheType);
typedef void (^BXHHTTPRequestFailureHandler)(id _Nullable response, NSException * _Nullable exception);
typedef void (^BXHHTTPRequestConfigHandler)(BXHHTTPRequestConfig * _Nonnull config);
typedef void (^BXHHTTPRequestCacheCompletionHandler)(BOOL cacheExpired);
typedef void (^BXHHTTPRequestNotificationListHandler)(NSArray * _Nullable notificationList);
typedef void (^BXHHTTPRequestBackendMessagesHandler)(NSArray * _Nullable messages);

#import <AFNetworking/AFNetworking.h>
NS_ASSUME_NONNULL_BEGIN

@interface BXHHTTPSessionManager : AFHTTPSessionManager


@property (nonatomic, strong, readonly) dispatch_semaphore_t _Nonnull semaphore;

/**
 *  创建网络请求体
 *
 *  @param URL host url
 *  @return 网络请求体实例
 */
+ (nonnull instancetype)sessionManagerWithBaseURL:(nonnull NSURL *)URL;
/**
 *  创建网络请求体
 *
 *  @param URL host url
 *  @param timeout 单个请求timeout时间
 *  @return 网络请求体实例
 */
+ (nonnull instancetype)sessionManagerWithBaseURL:(nonnull NSURL *)URL timeout:(NSTimeInterval)timeout;
/**
 *  手动添加HTTP header
 */
- (void)addValue:(nullable NSString *)value forHTTPHeaderField:(nonnull NSString *)field;

/**
 *  创建GET请求
 *
 *  @param configHandler 请求配置
 *  @param successHandler 请求成功返回
 *  @param failureHanlder 请求失败返回
 */
- (void)makeGetRequest:(nonnull BXHHTTPRequestConfigHandler)configHandler
               success:(nullable BXHHTTPRequestSuccessHandler)successHandler
               failure:(nullable BXHHTTPRequestFailureHandler)failureHanlder;

/**
 *
 *  创建GET请求
 *
 *  @param configHandler 请求配置
 *  @param downloadProgress 请求进度
 *  @param successHandler 请求成功返回
 *  @param failureHanlder 请求失败返回
 */
- (void)makeGetRequest:(nonnull BXHHTTPRequestConfigHandler)configHandler
              progress:(nullable void (^)(NSProgress * _Nonnull))downloadProgress
               success:(nullable BXHHTTPRequestSuccessHandler)successHandler
               failure:(nullable BXHHTTPRequestFailureHandler)failureHanlder;

/**
 *  创建POST请求
 *
 *  @param configHandler 请求配置
 *  @param successHandler 请求成功返回
 *  @param failureHanlder 请求失败返回
 */
- (void)makePostRequest:(nonnull BXHHTTPRequestConfigHandler)configHandler
                success:(nullable BXHHTTPRequestSuccessHandler)successHandler
                failure:(nullable BXHHTTPRequestFailureHandler)failureHanlder;

/**
 *  创建POST请求
 *
 *  @param configHandler 请求配置
 *  @param cacheHandler 缓存类型回调
 *  @param successHandler 请求成功返回
 *  @param failureHanlder 请求失败返回
 */
- (void)makePostRequest:(nonnull BXHHTTPRequestConfigHandler)configHandler
                  cache:(nullable BXHHTTPRequestCacheHandler)cacheHandler
                success:(nullable BXHHTTPRequestSuccessHandler)successHandler
                failure:(nullable BXHHTTPRequestFailureHandler)failureHanlder;

/**
 *  创建POST请求
 *
 *  @param configHandler 请求配置
 *  @param downloadProgress 请求进度
 *  @param successHandler 请求成功返回
 *  @param failureHanlder 请求失败返回
 */
- (void)makePostRequest:(nonnull BXHHTTPRequestConfigHandler)configHandler
               progress:(nullable void (^)(NSProgress * _Nonnull))downloadProgress
                success:(nullable BXHHTTPRequestSuccessHandler)successHandler
                failure:(nullable BXHHTTPRequestFailureHandler)failureHanlder;

/**
 *  创建POST请求
 *
 *  @param configHandler 请求配置
 *  @param cacheHandler 缓存类型回调
 *  @param downloadProgress 请求进度
 *  @param successHandler 请求成功返回
 *  @param failureHanlder 请求失败返回
 */
- (void)makePostRequest:(nonnull BXHHTTPRequestConfigHandler)configHandler
                  cache:(nullable BXHHTTPRequestCacheHandler)cacheHandler
               progress:(nullable void (^)(NSProgress * _Nonnull))downloadProgress
                success:(nullable BXHHTTPRequestSuccessHandler)successHandler
                failure:(nullable BXHHTTPRequestFailureHandler)failureHanlder;

@end

NS_ASSUME_NONNULL_END
