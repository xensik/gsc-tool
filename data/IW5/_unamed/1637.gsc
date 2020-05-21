// IW5 PC GSC
// Decompiled by https://github.com/xensik/gsc-tool

main()
{
    self setmodel( "body_london_male_a" );
    codescripts\character::attachHead( "alias_civilian_heads_male_drone", _ID1636::main() );
    self._ID2738 = "british";
}

precache()
{
    precachemodel( "body_london_male_a" );
    codescripts\character::precacheModelArray( _ID1636::main() );
}
