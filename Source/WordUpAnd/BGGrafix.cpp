#include "BGGrafix.h"

#include "BGGrafixObject.h"
#include "Tools.h"
#include "Components/DirectionalLightComponent.h"

ABGGrafix::ABGGrafix() {
	PrimaryActorTick.bCanEverTick = true;
	USceneComponent* root = GetRootComponent();
	if (!root) {
		root = CreateDefaultSubobject<USceneComponent>(FName("root"));
		SetRootComponent(root);
	}
	bg_plane = CreateDefaultSubobject<UStaticMeshComponent>(FName("bg plane"));
	direction_cone = CreateDefaultSubobject<UStaticMeshComponent>(FName("direction cone"));
	bg_plane->SetupAttachment(root);
	direction_cone->SetupAttachment(root);

	static ConstructorHelpers::FClassFinder<ABGGrafixObject>
		BGGrafixObject_BP(TEXT("/Game/Blueprints/BP_BGGrafixObject.BP_BGGrafixObject_C"));
	BP_BGGrafixObject = BGGrafixObject_BP.Class;	
}

void ABGGrafix::BeginPlay() {
	Super::BeginPlay();
	FVector min;
	FVector max;
	bg_plane->GetLocalBounds(min, max);
	spawn_radius_naive = FMath::Abs(min.Y);
	const FVector scale = bg_plane->K2_GetComponentScale();
	spawn_radius_naive *= scale.Y;
	direction_cone->SetVisibility(false);
	
	UWorld* world = GetWorld();
	for (int i = 0; i < obj_ct; ++i) {
		auto obj = Cast<ABGGrafixObject>(world->SpawnActor(BP_BGGrafixObject));
		if (obj) {
			objects.Add(obj);
		}
	}
	// TODO: from file
	if (objects.Num() > 0) {
		setBG(BGGRAFIX_PURPLE_PILLARS);
	}
}

void ABGGrafix::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	const FVector bg_loc = GetActorLocation();
	for (auto &obj : objects) {
		const FVector next_loc = obj->GetActorLocation() + obj_move_dir * speed + DeltaTime;
		const float next_dist_sq = (next_loc - bg_loc).SizeSquared();
		if (next_dist_sq > spawn_radius_sq * 2.0f) {
			obj->SetActorLocation(obj->spawn_loc);
		}
		else {
			obj->SetActorLocation(next_loc);
		}
	}
}

void ABGGrafix::setBG(BGGRAFIX_BG_NAME name) {
	obj_rotation.Pitch = pitch_rot;
	obj_rotation.Roll = travel_rot;
	objects[0]->SetActorRotation(obj_rotation);
	const FVector forward = objects[0]->GetActorForwardVector();
	const FVector right = objects[0]->GetActorRightVector();
	obj_move_dir = FVector::CrossProduct(forward, right).GetSafeNormal();
	const FVector origin = GetActorLocation() + FVector(200.0f, 0.0f, 0.0f);
	if (name == BGGRAFIX_PURPLE_PILLARS) {
		spawn_radius =  spawn_radius_naive + mesh_pillar->GetBoundingBox().GetSize().Z * purple_pillars_scale.Z;
		spawn_radius_sq = spawn_radius * spawn_radius;
		const FVector spawn_loc = origin - obj_move_dir * spawn_radius;
		bg_plane->SetMaterial(0, m_purple);
		for (auto& obj: objects) {
			obj->init(mesh_pillar, m_purple, purple_pillars_scale, obj_rotation);
			const FVector rand_spawn_lr_offset = (FMath::FRand() * 2.0f - 1.0f) * spawn_radius_naive * right;
			const FVector rand_init_progress_loc =
				origin - (FMath::FRand() * 2.0f - 1.0f) * spawn_radius * obj_move_dir + rand_spawn_lr_offset;
			obj->spawn_loc = spawn_loc + rand_spawn_lr_offset;
			obj->SetActorLocation(rand_init_progress_loc);
		}
	}
}

