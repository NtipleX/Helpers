#include "nxAnimator.h"
#include "GameFramework/CharacterMovementComponent.h"

void UnxAnimator::NativeUpdateAnimation(float val)
{
	Super::NativeUpdateAnimation(val);
	if (!Owner)
	{
		Owner = Cast<AnxHero>(TryGetPawnOwner());
	}
	else
	{
		/// Movement
		auto vel = Owner->GetVelocity();
		vel.Z = 0.f;
		MovementSpeed = vel.Size();
		IsInAir = Owner->GetCharacterMovement()->IsFalling();
		IsCrouched = Owner->GetCharacterMovement()->IsCrouching();
	}
}