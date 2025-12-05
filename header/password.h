#ifndef PASSWORD_H
#define PASSWORD_H

#include <stddef.h>
#include <stdbool.h>

#define PASSWORD_MAX_LEN 128
#define PASSWORD_SALT_LEN 16
#define PASSWORD_HASH_LEN 64

/**
 * Reads password from terminal (no echo).
 * Returns newly allocated buffer (must be freed by caller).
 */
char* password_read(void);

// Securely wipes memory of password or hash to prevent forensic recovery.
void password_secure_erase(void* buffer, size_t len);

/**
 * Generates a cryptographically secure random salt.
 * Salt buffer must be at least PASSWORD_SALT_LEN bytes.
 */
bool password_generate_salt(unsigned char* salt);

/**
 * Hashes a password with the given salt using SHA256 (for example).
 * Hash buffer must be at least PASSWORD_HASH_LEN bytes.
 */
bool password_hash(
    const char* password,
    const unsigned char* salt,
    unsigned char* out_hash
);

// Verifies input password against an existing salt + hash.
bool password_verify(
    const unsigned char* saved_hash,
    const unsigned char* saved_salt,
    const char* input_password
);

#endif // PASSWORD_H
