// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TraceHelper.h"
#include "nxHero.generated.h"

UCLASS()
class SURVRUN_API AnxHero : public ACharacter
{
	GENERATED_BODY()

public:

	AnxHero();


private:	// Overrides

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


private:	// UProperties

	UPROPERTY(EditDefaultsOnly, Category = nx)
	class USpringArmComponent* HeroSpring;
	UPROPERTY(EditDefaultsOnly, Category = nx)
	class UCameraComponent* HeroCamera;


private:	// Functions

	void moveForward(float val);
	void moveStrafe(float val);
	void lookUp(float val);
	void lookSide(float val);
	void crouch();
	void jump();
	void aimWeapon();
	void fireWeapon();
	void interact();


private:

	class UnxAnimator* m_animator;

};
