#include "BGGrafixObject.h"
#include "Tools.h"

ABGGrafixObject::ABGGrafixObject() {
	bggrafix_obj_type = BGGRAFIX_PILLAR;
}

void ABGGrafixObject::BeginPlay() {
	Super::BeginPlay();
	GetStaticMeshComponent()->SetMobility(EComponentMobility::Movable);
}

void ABGGrafixObject::init(
	UStaticMesh* static_mesh,
	UMaterial* material,
	const FVector& scale,
	const FRotator& rotation
) {
	UStaticMeshComponent* mesh = GetStaticMeshComponent();
	 mesh->SetStaticMesh(static_mesh);
	mesh->SetWorldScale3D(scale);
	mesh->SetWorldRotation(rotation);
	mesh->SetMaterial(0, material);
}
