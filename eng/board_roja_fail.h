en terminal uno:
openocd -f interface/cmsis-dap.cfg -f target/kx.cfg

en terminal 2:
telnet localhost 444

por telnet: si funca:
mdw 0x00000400 4
0x00000400: ffffffff ffffffff ffffffff fffffffe 

no funca:
mww 0x40048038 0x400


kinetis mdm mass_erase


La placa FRDM-KL28Z ha sufrido una falla funcional crítica en el silicio del microcontrolador, resultando en un estado de "brick" irreversible. El hardware se encuentra en un modo de seguridad parcial que impide la configuración de cualquier periférico, lo que la inutiliza por completo para fines de desarrollo y programación. Se recomienda su reemplazo.



