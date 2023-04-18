#pragma once

#include "CoreMinimal.h"
// we could use ECC_GameTraceChannel1 from the beging at APojectile.CPP to block the seletalMesh but this is more Descriptive 
#define ECC_SkeletalMesh ECollisionChannel::ECC_GameTraceChannel1 
#define ECC_HitBox ECollisionChannel::ECC_GameTraceChannel2

