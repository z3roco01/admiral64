# admiral64
An operating system for raspi3 to mimic a commodore like environment

# Aknowledgements
- Bootloader & inspo for mailbox code from [raspi3-tutorial](https://github.com/bztsrc/raspi3-tutorial/blob/master/03_uart1/) by bztsrc
- [Very helpful doc](https://www.raspberrypi.org/app/uploads/2012/02/BCM2835-ARM-Peripherals.pdf) for peripherials ( its for bcm2835 but the only difference is the arm core used )

# Planned Features
- [ ] SSFN font support ( will use temp font first )
- [ ] File reading
- [ ] Boot to BASIC interpreater ( may use uart if started before font )
- [ ] Assembler and asm debugger
- [ ] BASIC program format
- [ ] ELF execution support
## Potential Features
None of this is certain to come, but would be cool.
- [ ] C compiler
- [ ] Some sort of kernel module support ( maybe extract out kernel into modules )
