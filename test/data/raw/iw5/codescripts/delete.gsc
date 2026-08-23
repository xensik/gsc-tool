main()
{
	assert(isdefined(self));
	wait 0;
	if (isdefined(self))
		self delete();
}
