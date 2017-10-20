if ( ./pwn $1".pwn" )
	then echo "---- Compile Sucess ----"
else 
	echo "!!!!Erro de Compilação"
	rm $1."asm"
	exit	
fi

if ( yasm -f elf32 $1".asm" )
	then echo "---- Assemble Sucess ----"
else
	echo "!!!!Assemblying Error"
	exit
fi

if( ld -o $1 $1".o" -l rts )
	then echo "---- Exe Sucess ----"
else
	echo "!!!!Exe Failed"
	exit
fi 
