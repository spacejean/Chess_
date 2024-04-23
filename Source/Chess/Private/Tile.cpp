// Fill out your copyright notice in the Description page of Project Settings.


#include "Tile.h"

// Sets default values
ATile::ATile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// template function that creates a components
	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));

	// every actor has a RootComponent that defines the transform in the World
	SetRootComponent(Scene);
	StaticMeshComponent->SetupAttachment(Scene);
	CurrentMaterial = nullptr;
	OccupyingChessPiece = nullptr;
	Status = ETileStatus::EMPTY;
	PlayerOwner = -1;
	TileGridPosition = FVector2D(0, 0);

}

void ATile::SetTileStatus(const int32 TileOwner, const ETileStatus TileStatus)
{
	PlayerOwner = TileOwner;
	Status = TileStatus;
}

ETileStatus ATile::GetTileStatus()
{
	return Status;
}

int32 ATile::GetOwner()
{
	return PlayerOwner;
}

void ATile::SetGridPosition(const double InX, const double InY)
{
	TileGridPosition.Set(InX, InY);
}

FVector2D ATile::GetGridPosition()
{
	return TileGridPosition;
}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();

}

/*
void ATile::SetMaterial(UMaterialInterface* Material)
{
	if (Material)
	{
		StaticMeshComponent->SetMaterial(0, Material);
		CurrentMaterial = Material;
	}
}

*/

void ATile::SetMaterial(int32 Color)
{
	if (Color == 0)
	{
		StaticMeshComponent->SetMaterial(0, LightTile);
		CurrentMaterial = LightTile;
	}

	else if (Color == 1)
	{
		StaticMeshComponent->SetMaterial(0, DarkTile);
		CurrentMaterial = DarkTile;
	}

	else if (Color == 2)
	{
		StaticMeshComponent->SetMaterial(0, SelectedTile);
		
	}
	else if (Color == 3)
	{
		StaticMeshComponent->SetMaterial(0, SuggestedTile);
		//CurrentMaterial = SuggestedTile;
	}
	else if (Color == 4)
	{
		StaticMeshComponent->SetMaterial(0, CurrentMaterial);
	}
	else if (Color == 5)
	{
		StaticMeshComponent->SetMaterial(0, KillTile);
	}
}

UMaterialInstance* ATile::GetMaterial(int32 Color) const
{
	UMaterialInstance* Material = nullptr;

		switch (Color)
		{
		case 0:
			Material = LightTile;
			break;
		case 1:
			Material = DarkTile;
			break;
		case 2:
			Material = SelectedTile;
			break;
		case 3:
			Material = SuggestedTile;
			break;
		case 4:
			Material = CurrentMaterial;
			break;
		case 5:
			Material = KillTile;
			break;
		default:
			// Se il colore non è valido, restituisci nullptr o un'altra azione appropriata
			
			break;
		}
		return Material;	
}

void ATile::SetOccupyingChessPiece(ABasePiece* BasePiece)
{
	OccupyingChessPiece = BasePiece;
}

ABasePiece* ATile::GetOccupyingChessPiece() const
{
	return OccupyingChessPiece;
	
}

// Called every frame
//void ATile::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}

