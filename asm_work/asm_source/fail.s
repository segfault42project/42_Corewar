.name "corewar"
.comment ""

l2:



		sti 	   r1, %:live, 2
#						%9223372036854775807
		and r1, %0, r1

live:		live %1
		zjmp %:live
