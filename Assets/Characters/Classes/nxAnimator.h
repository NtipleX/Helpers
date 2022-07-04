// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Animation/AnimMontage.h"
#include "nxHero.h"
#include "nxAnimator.generated.h"

UCLASS()
class SURVRUN_API UnxAnimator : public UAnimInstance
{
	GENERATED_BODY()
public:

	UPROPERTY(EditDefaultsOnly, Category = nx)
	UAnimMontage* PickupMontage;

	UPROPERTY(BlueprintReadOnly, Category = nx);
	float MovementSpeed;

	UPROPERTY(BlueprintReadOnly, Category = nx);
	bool IsInAir;

	UPROPERTY(BlueprintReadOnly, Category = nx);
	bool IsCrouched;

	virtual void NativeUpdateAnimation(float val) override;

private:
	AnxHero* Owner;
};
