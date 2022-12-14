// Fill out your copyright notice in the Description page of Project Settings.


#include "PersonagemTPS.h"
#include "Components/InputComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"

// Sets default values
APersonagemTPS::APersonagemTPS()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmCamera = CreateDefaultSubobject<USpringArmComponent>(FName("SpringArmCamera"));
	SpringArmCamera->TargetArmLength = 200.f;
	SpringArmCamera->bUsePawnControlRotation = true;
	SpringArmCamera->AddRelativeLocation(FVector(0.f, 0.f, 50.f));
	SpringArmCamera->bEnableCameraLag = true;//ativa lag da camera
	SpringArmCamera->CameraLagSpeed = 40.f;//velocidade do lag
	SpringArmCamera->SetupAttachment(RootComponent);

	CameraPersonagem = CreateDefaultSubobject<UCameraComponent>(FName("CameraPersonagem"));
	CameraPersonagem->SetupAttachment(SpringArmCamera);

	GetMovementComponent()->GetNavAgentPropertiesRef().bCanCrouch = true;

	//--------Configuração do pulo-------------
	GetCharacterMovement()->AirControl = 0.05f;
	GetCharacterMovement()->JumpZVelocity = 425.f;
	GetCharacterMovement()->GravityScale = 1.5f;
	GetCharacterMovement()->CrouchedHalfHeight = 70.f;

	AutoPossessPlayer = EAutoReceiveInput::Player0;

}

// Called when the game starts or when spawned
void APersonagemTPS::BeginPlay()
{
	Super::BeginPlay();
	
}

//---------------Movimento--------------------
void APersonagemTPS::MoverParaFrente(float Valor)
{
	AddMovementInput(GetActorForwardVector() * Valor);
}

void APersonagemTPS::MoverDireita(float Valor)
{
	AddMovementInput(GetActorRightVector() * Valor);
}
//------------------Agachar--------------------
void APersonagemTPS::Agachar()
{
	Crouch();
}

void APersonagemTPS::Levantar()
{
	UnCrouch();
}

//------------------Pular--------------------

void APersonagemTPS::Pular()
{
	bEstaPulando = true;
}

void APersonagemTPS::PararPulo()
{
	bEstaPulando = false;
}

// Called every frame
void APersonagemTPS::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APersonagemTPS::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoverParaFrente", this, &APersonagemTPS::MoverParaFrente);
	PlayerInputComponent->BindAxis("MoverDireita", this, &APersonagemTPS::MoverDireita);

	PlayerInputComponent->BindAxis("OlharCimaBaixo", this, &APersonagemTPS::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("OlharDireitaEsquerda", this, &APersonagemTPS::AddControllerYawInput);

	PlayerInputComponent->BindAction("Agachar", EInputEvent::IE_Pressed, this, &APersonagemTPS::Agachar);
	PlayerInputComponent->BindAction("Agachar", EInputEvent::IE_Released, this, &APersonagemTPS::Levantar);

	PlayerInputComponent->BindAction("Pular", EInputEvent::IE_Pressed, this, &APersonagemTPS::Pular);
	PlayerInputComponent->BindAction("Pular", EInputEvent::IE_Released, this, &APersonagemTPS::PararPulo);
}

