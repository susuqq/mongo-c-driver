/*
 * Copyright 2016 MongoDB, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


#ifndef MONGOC_METADATA_PRIVATE_H
#define MONGOC_METADATA_PRIVATE_H

#if !defined (MONGOC_INSIDE) && !defined (MONGOC_COMPILATION)
# error "Only <mongoc.h> can be included directly."
#endif
#include <bson.h>

BSON_BEGIN_DECLS

#define METADATA_FIELD "client"
#define METADATA_PLATFORM_FIELD "platform"

#define METADATA_MAX_SIZE 512

#define METADATA_OS_TYPE_MAX 32
#define METADATA_OS_NAME_MAX 32
#define METADATA_OS_VERSION_MAX 32
#define METADATA_OS_ARCHITECTURE_MAX 32
#define METADATA_DRIVER_NAME_MAX 64
#define METADATA_DRIVER_VERSION_MAX 32
/* platform has no fixed max size. It can just occupy the remaining
 * available space in the document. */

/* When adding a new field to mongoc-config.h.in, update this! */
typedef enum
{
   MONGOC_MD_FLAG_ENABLE_CRYPTO                = 1 << 0,
   MONGOC_MD_FLAG_ENABLE_CRYPTO_CNG            = 1 << 1,
   MONGOC_MD_FLAG_ENABLE_CRYPTO_COMMON_CRYPTO  = 1 << 2,
   MONGOC_MD_FLAG_ENABLE_CRYPTO_LIBCRYPTO      = 1 << 3,
   MONGOC_MD_FLAG_ENABLE_CRYPTO_SYSTEM_PROFILE = 1 << 4,
   MONGOC_MD_FLAG_ENABLE_SASL                  = 1 << 5,
   MONGOC_MD_FLAG_ENABLE_SSL                   = 1 << 6,
   MONGOC_MD_FLAG_ENABLE_SSL_OPENSSL           = 1 << 7,
   MONGOC_MD_FLAG_ENABLE_SSL_SECURE_CHANNEL    = 1 << 8,
   MONGOC_MD_FLAG_ENABLE_SSL_SECURE_TRANSPORT  = 1 << 9,
   MONGOC_MD_FLAG_EXPERIMENTAL_FEATURES        = 1 << 10,
   MONGOC_MD_FLAG_HAVE_SASL_CLIENT_DONE        = 1 << 11,
   MONGOC_MD_FLAG_HAVE_WEAK_SYMBOLS            = 1 << 12,
   MONGOC_MD_FLAG_NO_AUTOMATIC_GLOBALS         = 1 << 13
} mongoc_metadata_config_flags_t;


typedef struct _mongoc_metadata_t
{
   char *os_type;
   char *os_name;
   char *os_version;
   char *os_architecture;

   char *driver_name;
   char *driver_version;
   char *platform;

   bool  frozen;
} mongoc_metadata_t;

void               _mongoc_metadata_init                       (void);
void               _mongoc_metadata_cleanup                    (void);

bool               _mongoc_metadata_build_doc_with_application (bson_t     *doc,
                                                                const char *application);
void               _mongoc_metadata_freeze                     (void);
mongoc_metadata_t *_mongoc_metadata_get                        (void);
bool               _mongoc_metadata_appname_is_valid           (const char *appname);
BSON_END_DECLS

#endif
