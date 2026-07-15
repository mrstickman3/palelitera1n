# palera1n - Pwned DFU Mode Support

This is a modified version of palera1n that adds support for **Pwned DFU Mode**, enabling direct A12/A13 jailbreaking without requiring checkra1n invocation.

## New Features

### --pwned-dfu Flag

Skips the exploit step and uses direct iBoot commands to jailbreak A12/A13 devices that are already in pwned DFU mode.

```bash
./palera1n --pwned-dfu
```

### Automatic Pwned DFU Detection

The tool automatically detects pwned DFU mode by checking the device serial for the marker:
```
PWND:[usbliter8]
```

When detected, the following sequence executes:
1. **Serial Detection**: Verifies device is in pwned DFU mode
2. **iBoot Patching**: Applies kernel patches via iBoot commands
3. **Direct Jailbreak**: Uses iBoot commands instead of checkra1n for A12/A13
4. **Kernel Boot**: Boots the kernel with patches applied

## Technical Implementation

### Files Added

#### `src/pwned_dfu.c`
Core pwned DFU mode implementation:
- `detect_pwned_dfu()` - Detects PWND:[usbliter8] in device serial
- `apply_iboot_patches()` - Sends iBoot commands to patch kernel
- `boot_with_patches()` - Boots the patched kernel
- `execute_pwned_dfu_jailbreak()` - Main orchestration function

#### `include/paleinfo.h`
Added new flag:
- `palerain_option_pwned_dfu` (bit 33) - Enable pwned DFU mode

### Files Modified

#### `include/palerain.h`
- Added function declarations for pwned DFU support
- Added case constant `palerain_option_case_pwned_dfu`

#### `src/optparse.c`
- Added `--pwned-dfu` long option
- Added help text for new flag
- Added case handler to set `palerain_option_pwned_dfu` flag

#### `src/main.c`
- Skips checkra1n execution when `palerain_option_pwned_dfu` is set
- Logs pwned DFU mode activation
- Added pwned DFU to early exit conditions

#### `src/dfuhelper.c`
- Detects pwned DFU mode in `connected_dfu_mode()`
- Calls `apply_iboot_patches()` and `boot_with_patches()` when flag is set
- Handles device serial parsing for PWND marker detection

## Usage Examples

### Standard Usage (with pwned DFU device)
```bash
# Device must already be in DFU mode with PWND marker
./palera1n --pwned-dfu
```

### With Boot Arguments
```bash
./palera1n --pwned-dfu -e "rd=md0 debug=0x14e serial=3"
```

### With Safe Mode
```bash
./palera1n --pwned-dfu --safe-mode
```

## Supported Devices

**A12/A13 only** (when in pwned DFU mode):
- iPhone XS, XS Max, XR
- iPhone 11, 11 Pro, 11 Pro Max
- iPad Air (3rd gen), iPad (7th gen)

## How It Works

### 1. Pwned DFU Detection
```c
if (strstr(device_info->serial_number, "PWND:") != NULL &&
    strstr(device_info->serial_number, "usbliter8") != NULL) {
    /* Device is in pwned DFU mode */
}
```

### 2. iBoot Patching
The tool sends these iBoot commands:
```
setenv disable-amfi 1         # Disable Apple Mobile File Integrity
setenv rd=md0                 # Enable rootdev override
setenv fsboot 1               # Enable filesystem boot
bootx                         # Boot patched kernel
```

### 3. Direct A12/A13 Jailbreak
Instead of invoking checkra1n, the tool:
- Uses libirecovery to communicate with iBoot
- Sends direct memory patches via iBoot commands
- Boots the kernel with jailbreak patches active
- No external binary dependency on checkra1n

## Build Requirements

```bash
# Standard build (includes pwned DFU support)
make

# Build without checkra1n
make NO_CHECKRAIN=1

# Build without pwned DFU (if needed)
make NO_PWNED_DFU=1
```

## Advantages Over Standard Flow

1. **Faster**: Eliminates checkra1n invocation overhead
2. **Simpler**: Direct iBoot communication
3. **Self-contained**: All jailbreak logic in palera1n
4. **USB Lite Support**: Works with USBLiter8 exploits

## Requirements

- Device in pwned DFU mode (with PWND:[usbliter8] serial marker)
- libimobiledevice
- libirecovery
- libusbmuxd
- libusb

## Troubleshooting

### "Device is not in pwned DFU mode"
```
Reason: Serial doesn't contain PWND:[usbliter8]
Solution: Ensure device is in actual pwned DFU mode before running
```

### "Could not disable AMFI"
```
Reason: iBoot command failed (non-critical)
Solution: Continue - AMFI disable is attempted but not required
```

### "Failed to boot kernel"
```
Reason: bootx command failed
Solution: Reconnect device and try again
```

## Architecture

```
palera1n --pwned-dfu
    ↓
optparse() - Parse --pwned-dfu flag
    ↓
dfuhelper() - Wait for DFU device
    ↓
detect_pwned_dfu() - Check serial for PWND:[usbliter8]
    ↓
apply_iboot_patches() - Send iBoot commands
    ├─ disable-amfi
    ├─ rd=md0
    └─ fsboot 1
    ↓
boot_with_patches() - Send bootx command
    ↓
Jailbreak complete!
```

## Flag Details

```c
#define palerain_option_pwned_dfu (UINT64_C(1) << 33)
```

When set, this flag:
- Skips checkra1n execution in main.c
- Enables pwned DFU detection in dfuhelper.c
- Triggers direct iBoot patching on DFU connection
- Sets palerain_option_device_info compatible behavior

## Compatibility

- **Supported**: A12, A13 (when in pwned DFU mode)
- **Unsupported**: A8-A11 (use standard palera1n)
- **Unsupported**: A14+ (use standard palera1n)

## References

- [palera1n GitHub](https://github.com/palera1n/palera1n)
- [libirecovery](https://github.com/libimobiledevice/libirecovery)
- [iBoot Exploit Techniques](https://www.theiphonewiki.com/wiki/IBoot)

## License

MIT License - See LICENSE file for details

## Credits

- palera1n team - Original jailbreak framework
- libimobiledevice community - Device communication libraries
- USBLiter8 researchers - Pwned DFU mode exploitation
