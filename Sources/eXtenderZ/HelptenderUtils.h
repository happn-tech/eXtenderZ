/*
 * HelptenderUtils.h
 * happn
 *
 * Created by François LAMBOLEY on 30/04/14.
 * Copyright (c) 2014-2018 happn. All rights reserved.
 */

@import ObjectiveC.runtime;



#define HPN_HELPTENDER_CALL_SUPER_NO_ARGS(className) \
	class_getMethodImplementation([self hpn_getSuperClassWithOriginalHelptenderClass:className.class], _cmd))(self, _cmd

#define HPN_HELPTENDER_CALL_SUPER(className, ...) \
	class_getMethodImplementation([self hpn_getSuperClassWithOriginalHelptenderClass:className.class], _cmd))(self, _cmd, __VA_ARGS__

#define HPN_HELPTENDER_CALL_SUPER_WITH_SEL_NAME(className, sel_name, ...) \
	class_getMethodImplementation([self hpn_getSuperClassWithOriginalHelptenderClass:className.class], @selector(sel_name)))(self, @selector(sel_name), __VA_ARGS__


@interface NSObject (ForHelptendersOnly)

- (Class)hpn_getSuperClassWithOriginalHelptenderClass:(Class)originalHelptenderClass;

@end


/* *** */

#define HPN_DYNAMIC_ACCESSOR(type, name, key)                                                                                                                                                \
	- (type *)name                                                                                                                                                                        \
	{                                                                                                                                                                                     \
		return [self name##CreateIfNotExist:NO];                                                                                                                                           \
	}                                                                                                                                                                                     \
	                                                                                                                                                                                      \
	- (type *)name##CreateIfNotExist:(BOOL)createIfNeeded                                                                                                                                 \
	{                                                                                                                                                                                     \
		id ret = [self hpn_getAssociatedObjectWithKey:&key createIfNotExistWithBlock:(createIfNeeded? ^id{                                                                                  \
			return [[type alloc] initWithCapacity:7];                                                                                                                                       \
		}: NULL)];                                                                                                                                                                         \
																																																													  \
		NSAssert(ret == nil || [ret isKindOfClass:type.class], @"***** INTERNAL ERROR: Got invalid (not of class "S(type)") associated object %@ in %@", ret, NSStringFromSelector(_cmd)); \
		return ret;                                                                                                                                                                        \
	}