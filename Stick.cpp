#include "Stick.h"
#include "Sphere1.h"


// Sets default values
AStick::AStick()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Stick");

}

// Called when the game starts or when spawned
void AStick::BeginPlay()
{
	Super::BeginPlay();

	startangle = 0.0f;
	sign = 1.0f;
	down = false;
	x0 = GetActorLocation();
	a = 0.0f;
	b = 90.0f;
	angle = 0.0f;
	angle2 = 0.0872665f;
	velocity = 0.0f;
	gravity = FVector(0.0f, 0.0f, 3.8f);
	Position = FVector(1.0f, 0.0f, 1.0f);
	m1 = 2.0f;
	m2 = 2.0f;
	
}

void AStick::changedown() {
	down = true;
}

// Called every frame
void AStick::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	T += 6.0f*DeltaTime;

	velocity2 += ((2.0 / 3.0)*gravity.Z * (sin(angle2)));
	if (!down) {


		velocity += gravity.Z * (cos(angle)) * (-m1-m2);

		Position.Z = -1.0f / 2.0f*velocity*(cos(angle)) * (-m1-m2)+ x0.Z;

		Position.X = 1.0f / 2.0f*velocity*(sin(angle)) * (-m1-m2) + x0.X;


		SetActorLocation((FVector(Position.X + Position2.X, GetActorLocation().Y, Position.Z + Position2.Z)));
	}
	else {
		if (a >= b) {
			down = false;
			b += 180.0f;
		}
	}
	a = velocity2*T / 2.5f;

	angle = a*(3.14159265359 / 180.0f);
}

