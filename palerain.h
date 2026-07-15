/*
 * palerain - https://github.com/palera1n/palerain
 *
 * This file is part of palerain
 * 
 * SPDX-License-Identifier: MIT
 */

#ifndef PALERAIN_H
#define PALERAIN_H

#include <libirecovery.h>
#include <libimobiledevice/libimobiledevice.h>
#include <usbmuxd.h>
#include <pthread.h>
#include <paleinfo.h>

#define BUILD_COMMIT_PLACEHOLDER "commit"
#define PALERAIN_VERSION "2.1-pwned-dfu"

enum {
    palerain_option_case_libcheckra1nhelper_path = 257,
    palerain_option_case_force_revert = 258,
    palerain_option_case_version = 259,
    palerain_option_case_cli = 260,
};

typedef int (*pthread_start_t)(void *arg);
typedef unsigned int usb_ret_t;

typedef struct {
    int mode;
    int cpid;
    char product_type[0x20];
    char display_name[0x20];
    char iboot_ver[0x20];
} recvinfo_t;

typedef struct {
    uint32_t magic; /* 0xd803b376*/
    unsigned char* ptr; /* pointer to the override file in memory */
    uint32_t len; /* length of override file */
    unsigned char* orig_ptr; /* pointer to the overriden file */
    uint32_t orig_len; /* length of the overriden file */
    int fd; /* file descriptor of the override file */
} override_file_t;

typedef unsigned char niarelap_file_t[];

extern unsigned int verbose;

extern char* pongo_path;
#ifdef TUI
extern bool tui_started;
#endif

extern uint64_t palerain_flags;
extern uint64_t* palerain_flags_p;

extern pthread_t dfuhelper_thread, pongo_thread;
extern int pongo_thr_running, dfuhelper_thr_running;

extern niarelap_file_t *kpf_to_upload_1, *ramdisk_to_upload_1, *overlay_to_upload_1;
extern niarelap_file_t **kpf_to_upload, **ramdisk_to_upload, **overlay_to_upload;
extern override_file_t override_ramdisk, override_kpf, override_overlay;

extern uint64_t palerain_flags;
extern pthread_mutex_t log_mutex;

extern pthread_mutex_t spin_mutex, found_pongo_mutex, ecid_dfu_wait_mutex;

extern int pongo_thr_running, dfuhelper_thr_running;
extern bool device_has_booted;
extern char xargs_cmd[0x270];
extern char palerain_flags_cmd[0x30];
extern char* ext_checkra1n;

int log_level_t;

void thr_cleanup(void* ptr);
void* dfuhelper(void* ptr);
int p1_log(log_level_t loglevel, const char *fname, int lineno, const char *fxname, const char* __restrict format, ...);
/* devhelper helpers */
struct devinfo_s;
typedef struct devinfo_s devinfo_t;
void devinfo_free(devinfo_t *dev);
bool cpid_is_arm64(unsigned int cpid);
/* devhelper commands */
int subscribe_cmd(void* device_event_cb, void* irecv_device_event_cb);
int unsubscribe_cmd(void);
int devinfo_cmd(devinfo_t *dev, const char *udid);
int enter_recovery_cmd(const char* udid);
int reboot_cmd(const char* udid);
int passstat_cmd(unsigned char* status, const char* udid);
int recvinfo_cmd(recvinfo_t* info, const uint64_t ecid);
int autoboot_cmd(const uint64_t ecid);
int exitrecv_cmd(const uint64_t ecid);

int exec_checkra1n(void);
int override_file(override_file_t *finfo, niarelap_file_t** orig, unsigned int *orig_len, char *filename);
void* pongo_helper(void* ptr);
const unsigned char *
boyermoore_horspool_memmem(const unsigned char* haystack, size_t hlen,
                           const unsigned char* needle,   size_t nlen);

/* Pwned DFU mode support */
int detect_pwned_dfu(irecv_device_t device);
int apply_iboot_patches(irecv_device_t device, unsigned int cpid);
int boot_with_patches(irecv_device_t device);

usb_ret_t USBControlTransfer(usb_device_handle_t handle, uint8_t bmRequestType, uint8_t bRequest, uint16_t wValue, uint16_t wIndex, uint32_t wLength, void *data, uint32_t *wLenDone);
const char *usb_strerror(usb_ret_t err);
int wait_for_pongo(void);
int tui(void);
int optparse(int argc, char* argv[]);

bool get_spin(void);
bool set_spin(bool val);
bool get_found_pongo(void);
void* pongo_helper(void* _);
bool set_found_pongo(bool val);
uint64_t get_ecid_wait_for_dfu(void);
uint64_t set_ecid_wait_for_dfu(uint64_t ecid);

void io_start(void* stuff);
void io_stop(void* stuff);

void print_credits(void);

#define LOG_VERBOSE 4
#define LOG_VERBOSE2 5
#define LOG_VERBOSE3 6
#define LOG_VERBOSE4 7
#define LOG_INFO 1
#define LOG_WARNING 2
#define LOG_ERROR 3
#define LOG_FATAL 0

#define LOG(level, ...) p1_log((level), __FILE__, __LINE__, __FUNCTION__, __VA_ARGS__)

#endif
