//
//  BXHHTTPSessionManager.m
//  AFNetworking
//
//  Created by baishuang on 2021/1/11.
//

#import "BXHHTTPSessionManager.h"
#import "BXHHTTPResponseSerializer.h"
#import "BXHHTTPSessionManager+GET.h"

@interface BXHHTTPSessionManager ()

@property (nonatomic, strong, readwrite) dispatch_semaphore_t semaphore;
//@property (nonatomic, strong, readwrite) YITCache *cache;
@end

@implementation BXHHTTPSessionManager


+ (instancetype)sessionManagerWithBaseURL:(NSURL *)URL {
#ifdef DEBUG
    return [self sessionManagerWithBaseURL:URL timeout:30.f];
#else
    return [self sessionManagerWithBaseURL:URL timeout:15.f];
#endif
}

+ (instancetype)sessionManagerWithBaseURL:(NSURL *)URL timeout:(NSTimeInterval)timeout {
    NSURLSessionConfiguration *config = [NSURLSessionConfiguration defaultSessionConfiguration];
    config.timeoutIntervalForRequest = timeout;
    BXHHTTPSessionManager *sessionManager = [[BXHHTTPSessionManager alloc] initWithBaseURL:URL sessionConfiguration:config];

//    BXHHTTPSessionManager *sessionManager = [[BXHHTTPSessionManager alloc] initWithBaseURL:URL sessionConfiguration:config];
    sessionManager.requestSerializer.HTTPShouldHandleCookies = NO;
    sessionManager.responseSerializer = [BXHHTTPResponseSerializer serializer];
    sessionManager.responseSerializer.acceptableContentTypes = [NSSet setWithObjects:@"text/html",@"application/json", @"text/json",@"text/plain",@"text/seg", nil];
    sessionManager.semaphore = dispatch_semaphore_create(0);
//    // network cache
//    sessionManager.cache = [YITCache sharedCacheWithName:@"YITNetworkCache"];
    [sessionManager addValue:@"application/x-www-form-urlencoded;charset=UTF-8" forHTTPHeaderField:@"Content-Type"];
    [sessionManager addValue:@"gzip" forHTTPHeaderField:@"Accept-Encoding"];
    [sessionManager addValue:@"close" forHTTPHeaderField:@"Connection"];
    
    if (![[NSUserDefaults standardUserDefaults] objectForKey:@"UserAgent"]) {
        [self setUserAgent];
    }
    NSString *userAgent = [[NSUserDefaults standardUserDefaults] objectForKey:@"UserAgent"];
    [sessionManager addValue:userAgent forHTTPHeaderField:@"User-Agent"];
    return sessionManager;
}

- (void)addValue:(NSString *)value forHTTPHeaderField:(NSString *)field {
    [self.requestSerializer setValue:value forKey:field];
}

-(void)makeGetRequest:(BXHHTTPRequestConfigHandler)configHandler success:(BXHHTTPRequestSuccessHandler)successHandler failure:(BXHHTTPRequestFailureHandler)failureHanlder {
    [self bxh_makeGetRequest:configHandler progress:nil success:successHandler failure:failureHanlder];
}

-(void)makeGetRequest:(BXHHTTPRequestConfigHandler)configHandler progress:(void (^)(NSProgress * _Nonnull))downloadProgress success:(BXHHTTPRequestSuccessHandler)successHandler failure:(BXHHTTPRequestFailureHandler)failureHanlder {
    [self bxh_makeGetRequest:configHandler progress:downloadProgress success:successHandler failure:failureHanlder];
}




#pragma mark - <Private Methods>

+ (void)setUserAgent {
    //传版本号 浏览器识别符 userAgent
    NSString *userAgent = [[[UIWebView alloc] init] stringByEvaluatingJavaScriptFromString:@"navigator.userAgent"];
    if (userAgent) {
        if (![userAgent containsString:@"httpagent"]) {
            NSMutableDictionary *mDic = [[NSMutableDictionary alloc] init];
            mDic[@"httpagent"] = userAgent;
            mDic[@"version"] = @"0.0.1";//[YITAppInfo appVersion];
            mDic[@"appid"] = @"3";
//            [[NSUserDefaults standardUserDefaults] registerDefaults:@{@"UserAgent": [mDic mj_JSONString]}];
        } else {
            [[NSUserDefaults standardUserDefaults] registerDefaults:@{@"UserAgent": userAgent}];
        }
    } else {
        NSMutableDictionary *mDic = [[NSMutableDictionary alloc] init];
        mDic[@"version"] = @"0.0.1"; //[YITAppInfo appVersion];
        mDic[@"appid"] = @"3";
//        [[NSUserDefaults standardUserDefaults] registerDefaults:@{@"UserAgent": [mDic mj_JSONString]}];
    }
}

@end
