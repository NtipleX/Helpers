#include "nxHero.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "nxAnimator.h"
#include "GameFramework/CharacterMovementComponent.h"

AnxHero::AnxHero()
{
	/// Creation
	HeroSpring = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	HeroCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));

	/// Attachment
	HeroSpring->SetupAttachment(RootComponent);
	HeroCamera->SetupAttachment(HeroSpring, USpringArmComponent::SocketName);

	/// Positioning
	HeroSpring->SetRelativeLocation(FVector(0, 0, 50));
	HeroSpring->SetRelativeRotation(FRotator(30, 0, 0));

	/// Configuration
	PrimaryActorTick.bCanEverTick = true;
	HeroSpring->TargetArmLength = 250.f;
	HeroSpring->bUsePawnControlRotation = true;
	HeroSpring->bInheritRoll = false;
	bUseControllerRotationYaw = false;

	//Movement
	UCharacterMovementComponent* mover = GetCharacterMovement();
	mover->bOrientRotationToMovement = true;
	mover->RotationRate = FRotator(0, 600, 0);
	mover->JumpZVelocity = 700.f;
	mover->AirControl = 1.f;
	mover->MaxWalkSpeedCrouched = 200.f;
	mover->CrouchedHalfHeight = 0.5f;

}

void AnxHero::BeginPlay()
{
	Super::BeginPlay();
	m_animator = Cast<UnxAnimator>(GetMesh()->GetAnimInstance());
}

void AnxHero::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AnxHero::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &AnxHero::moveForward);
	PlayerInputComponent->BindAxis("MoveStrafe", this, &AnxHero::moveStrafe);
	PlayerInputComponent->BindAxis("LookUp", this, &AnxHero::lookUp);
	PlayerInputComponent->BindAxis("LookSide", this, &AnxHero::lookSide);
	
	PlayerInputComponent->BindAction("Interact", IE_Released, this, &AnxHero::interact);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AnxHero::jump);
	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &AnxHero::crouch);
	PlayerInputComponent->BindAction("FireWeapon", IE_Pressed, this, &AnxHero::fireWeapon);
	PlayerInputComponent->BindAction("AimWeapon", IE_Pressed, this, &AnxHero::aimWeapon);
}

void AnxHero::moveForward(float val)
{
	AddMovementInput(HeroCamera->GetForwardVector() * val);
}

void AnxHero::moveStrafe(float val)
{
	if (val != 0.f)
	{
		FRotator rot = GetControlRotation();
		rot.Yaw += 90 * FMath::Sign(val);
		FQuat SideQuat{ rot };
		AddMovementInput(SideQuat.GetAxisX());
	}
}

void AnxHero::lookUp(float val)
{
	AddControllerPitchInput(val*-1);
}

void AnxHero::lookSide(float val)
{
	AddControllerYawInput(val);
}

void AnxHero::crouch()
{
	if (!bIsCrouched)
		Crouch(true);
	else
		UnCrouch(true);
}

void AnxHero::jump()
{
	Jump();
}

void AnxHero::aimWeapon()
{
}

void AnxHero::fireWeapon()
{
}

void AnxHero::interact()
{
	if (m_animator)
	{
		m_animator->Montage_Play(m_animator->PickupMontage, 1.5);
	}
}
