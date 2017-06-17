/*
*
*
*	Here's the info that users have to use to write password value.	
*
*
*/

#define NVP_INFO_TAG	"_pw"

/*
*
*
*
*
*
*
*
*/

#if defined _nvp_included
  #endinput
#endif
#define _nvp_included

#include <nvault>

new gVault;
new gVaultName[] = "NvaultPasswords";


/**
 * 	Open the NvaulPasswords.vault file
 * @noreturn
 */
stock nvp_open( )
{
	gVault = nvault_open( gVaultName );

	if( gVault == INVALID_HANDLE )
	{
		set_fail_state( " Problems with Nvault Passwords .vault  ... " );
	}
}

/**
 * 	Close the NvaultPasswords.vault file.
 * @noreturn
 */
stock nvp_close( ) nvault_close( gVault );


/**
 * Save an password to an index, in the vault will be saved SteamID and Password.
 *
 * @param	id			The index of the player.
 * @param	Password		The password to save( as integer ) .
 * @noreturn
 */
stock nvp_set_password( id, Password)
{
	new szAuthId[34]; get_user_authid( id, szAuthId, charsmax(szAuthId) );

	new szData[11];
	num_to_str( Password, szData, charsmax( szData ) );

	nvault_set( gVault, szAuthId, szData );
}


/*
*
*
*	Return true if the user password matches with his steamID.
*	Return false if user have no data in vault or the password doesn't match
*
*
*/
stock bool:nvp_user_password(id)
{
	new szAuthId[34]; get_user_authid( id, szAuthId, charsmax(szAuthId) );
	new iData = nvault_get( gVault, szAuthId );

	new PasswordData[11]; get_user_info( id, NVP_INFO_TAG, PasswordData, charsmax(PasswordData) );

	return bool:( iData != 0 && iData == str_to_num(PasswordData) );
}



/**
 * 	Reset the vault, so it deletes all the entries 
 * @noreturn
 */
stock nve_reset( )
{
	nvault_prune( gVault, 0, get_systime( ) );
}
