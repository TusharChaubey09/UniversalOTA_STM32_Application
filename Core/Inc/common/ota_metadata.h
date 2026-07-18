#ifndef OTA_METADATA_H
#define OTA_METADATA_H

#include "ota_types.h"

extern OTA_Metadata_t gOtaMetadata;

void OTA_MetadataSave(OTA_Metadata_t *metadata);

void OTA_MetadataRead(OTA_Metadata_t *metadata);

void OTA_MetadataLoadDummy(void);

#endif
