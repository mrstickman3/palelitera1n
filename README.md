# palera1n for usbliter8

btw like 90% of this was made with github copilot


A jailbreak for A12-A13


btw literally NONE of this is tested, if it works or doesnt work you should add an issue and if you have a fix, then a pull request
 

## Device Support

<!--- Mobile --->

| iPhone(s)                 | iPad(s)                        		| Apple TV(s)        			|
|-							|-										|-								|								
| iPhone XS                 | iPad Air (3rd gen)        			| Apple TV 4K (2nd generation)  |                     	
| iPhone XS Max             | iPad mini (5th generation)	    	|								|                            	
| iPhone XR                 | iPad (8th generation)					|								|								
| iPhone 11                 | iPad (9th generation) 				|								|								
| iPhone 11 Pro             |               						|								|								
| iPhone 11 Pro Max         |           							|								|                               
| iPhone SE (2nd gen)       |               						|								|								




## Usage 
i dont even know if this part even works tbh
```
Usage: palera1n [-DEhpvVdsSLRnPI] [-e boot arguments] [-k Pongo image] [-o overlay file] [-r ramdisk file] [-K KPF file] [-i checkra1n file]

	--version				Print version
	--force-revert				Remove jailbreak
	-d, --demote				Demote
	-D, --dfuhelper				Exit after entering DFU
	-e, --boot-args <boot arguments>	XNU boot arguments
	-E, --enter-recovery			Enter recovery mode
	-h, --help				Show this help
	-i, --override-checkra1n <file>		Override checkra1n
	-k, --override-pongo <file>		Override Pongo image
	-K, --override-kpf <file>		Override kernel patchfinder
	-L, --jbinit-log-to-file		Make jbinit log to /cores/jbinit.log (can be read from sandbox while jailbroken)
	-n, --exit-recovery			Exit recovery mode
	-I, --device-info			Print info about the connected device
	-o, --override-overlay <file>		Override overlay
	-p, --pongo-shell			Boots to PongoOS shell
	-P, --pongo-full			Boots to a PongoOS shell with default images already uploaded
	-r, --override-ramdisk <file>		Override ramdisk
	-R, --reboot-device			Reboot connected device in normal mode
	-s, --safe-mode				Enter safe mode
	-S, --no-colors				Disable colors on the command line
	-v, --debug-logging			Enable debug logging
		  This option can be repeated for extra verbosity.
	-V, --verbose-boot			Verbose boot

Environmental variables:
	TMPDIR		temporary diretory (path the built-in checkra1n will be extracted to)
```


## Credits

Paradigm Shift - usbliter8

Palera1n - Palera1n

