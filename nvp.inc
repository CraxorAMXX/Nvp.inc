#if defined _nvp_included
  #endinput
#endif
#define _nvp_included

#include <nvault>

new gVault;
new gVaultName[] = "NewVaultPie";
new bool:Opened;


/**
 *
 *
 *
 *
 *
 * 	Open the vault.
 * 	@noreturn
 *
 *
 *
 *
 */
stock nvp_open( )
{
	if( Opened == false )
	{
		Opened = true;
		gVault = nvault_open( gVaultName );

		if( gVault == INVALID_HANDLE )
		{
			set_fail_state( " Problems with Nvault Passwords .vault  ... " );
		}
	}
}

/**
 *
 *
 *
 *
 * 	Close the vault.
 * 	@noreturn
 *
 *
 *
 */
stock nvp_close( ) 
{
	if( Opened == true )
	{
		nvault_close( gVault );
		Opened = false;
	}
}


/**
 * Save an integer to an index.
 *
 * @param	id			The index of the player.
 * @pram	Symbol[]		The Symbol to make unique the save for your needs/plugin.
 * @param	Integer			The Integer to save.
 * @noreturn
 */
stock nvp_set_integer( id, const Symbol[], int)
{
	new szAuthId[34]; get_user_authid( id, szAuthId, charsmax(szAuthId) );
	new buffer[64]; formatex( buffer, charsmax(buffer), "%s%s", szAuthId, Symbol );

	new szData[11]; num_to_str( int, szData, charsmax( szData ) );

	nvault_set( gVault, buffer, szData );
}


/**
 * Retrieve an integer from an index.
 *
 * @param	id			The index of the player.
 * @param	Symbol[]		The symbol to perform the search.
 * @param	Integer			The Integer to save.
 * @return	The Integer result.
 */
stock nvp_get_integer( id, const Symbol[] )
{
	new szAuthId[34]; get_user_authid( id, szAuthId, charsmax(szAuthId) );
	new buffer[64]; formatex( buffer, charsmax(buffer), "%s%s", szAuthId, Symbol );

	new iData = nvault_get( gVault, buffer );
	return iData != 0 ? iData : 0;
}

/**
 * Save an string to an index.
 *
 * @param	id			The index of the player.
 * @pram	Symbol[]		The Symbol to make unique the save for your needs/plugin.
 * @param	String[]		The string to save.
 * @noreturn
 */
stock nvp_set_string( id, const Symbol[], const String[])
{
	new szAuthId[34]; get_user_authid( id, szAuthId, charsmax(szAuthId) );
	new buffer[64]; formatex( buffer, charsmax(buffer), "%s%s", szAuthId, Symbol );

	nvault_set( gVault, buffer, String );
}


/**
 * Retrieve an string from an index.
 *
 * @param	id			The index of the player.
 * @param	Symbol[]		The symbol to perform the search.
 * @param	String[]		The string to copy data from the savement.
 * @param	maxchars		The lengh of the String[] ( use charsmax(String[]) ).
 * @noreturn
 */
stock nvp_get_string( id, const Symbol[], const String[], maxchars=0 )
{
	new szAuthId[34]; get_user_authid( id, szAuthId, charsmax(szAuthId) );
	new buffer[64]; formatex( buffer, charsmax(buffer), "%s%s", szAuthId, Symbol );

	nvault_get( gVault, buffer, String, maxchars );
}


/**
 * 	Reset the vault, so it deletes all the entries 
 * 	@noreturn
 */
stock nvp_reset( )
{
	nvault_prune( gVault, 0, get_systime( ) );
}
