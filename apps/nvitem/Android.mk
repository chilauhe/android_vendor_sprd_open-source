ifneq ($(TARGET_SIMULATOR),true)
LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_C_INCLUDES    +=  $(LOCAL_PATH) \
			$(LOCAL_PATH)/common \
			vendor/sprd/open-source/apps/engineeringmodel/engcs
LOCAL_SRC_FILES:= \
	nvitem_buf.c \
	nvitem_fs.c \
	nvitem_os.c \
	nvitem_packet.c \
	nvitem_server.c \
	nvitem_sync.c	

ifeq ($(strip $(TARGET_BOARD_PLATFORM)),sc8830)
LOCAL_SRC_FILES += nvitem_channe_spipe.c
else
LOCAL_SRC_FILES += nvitem_channel.c
endif

LOCAL_SHARED_LIBRARIES := \
    libhardware_legacy \
    libc \
    libutils liblog \
    libengclient

#ifeq ($(strip $(TARGET_USERIMAGES_USE_EXT4)),true)
#LOCAL_CFLAGS := -DCONFIG_EMMC
#endif

LOCAL_MODULE := nvitemd
LOCAL_MODULE_TAGS := optional
include $(BUILD_EXECUTABLE)
endif