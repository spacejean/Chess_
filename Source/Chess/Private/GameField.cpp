// Fill out your copyright notice in the Description page of Project Settings.
//TODO cambiare TileScale per PieceScale

#include "GameField.h"
#include "Kismet/GameplayStatics.h"
#include "Managers/Chess_GameMode.h"

// Sets default values
AGameField::AGameField()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	//NONVA
	// size of winnning line
	WinSize = 3;
	// size of the field (3x3)
	Size = 8;
	// tile dimension
	TileSize = 120;
	


}


// Called when the game starts or when spawned
void AGameField::BeginPlay()
{
	Super::BeginPlay();
	GenerateField();
	GeneratePieces();
}




void AGameField::GenerateField()
{
	FVector Location0 = AGameField::GetRelativeLocationByXYPosition(0, 0);

	ATile* Obj1 = GetWorld()->SpawnActor<ATile>(TileClass0, Location0, FRotator::ZeroRotator);
	const float TileScale1 = TileSize / 100;
	Obj1->SetActorScale3D(FVector(TileScale1, TileScale1, 0.15));
	for (int32 x = 0; x < Size; x++)
	{
		for (int32 y = 0; y < Size; y++)
		{
			// Check if the tile is dark or light based on its position
			bool bIsDark = (x + y) % 2 == 0;

			// Set the material based on whether the tile is dark or light
			if (bIsDark)
			{
				FVector Location = AGameField::GetRelativeLocationByXYPosition(x, y);
				ATile* Obj = GetWorld()->SpawnActor<ATile>(TileClass, Location, FRotator::ZeroRotator);
				//UMaterialInstance* SelectTile1 = Cast<UMaterialInstance>(StaticLoadObject(UMaterialInstance::StaticClass(), nullptr, TEXT("/Game/Materials/M_BTile")));
				Obj->SetMaterial(1);
				const float TileScale = TileSize / 100;
				Obj->SetActorScale3D(FVector(TileScale, TileScale, 0.2));
				Obj->SetGridPosition(x, y);
				TileArray.Add(Obj);
				TileMap.Add(FVector2D(x, y), Obj);

			}
			else
			{
				FVector Location = AGameField::GetRelativeLocationByXYPosition(x, y);
				ATile* Obj = GetWorld()->SpawnActor<ATile>(TileClass, Location, FRotator::ZeroRotator);
				//UMaterialInstance* SelectTile1 = Cast<UMaterialInstance>(StaticLoadObject(UMaterialInstance::StaticClass(), nullptr, TEXT("/Game/Materials/M_WTile")));
				Obj->SetMaterial(0);
				const float TileScale = TileSize / 100;
				Obj->SetActorScale3D(FVector(TileScale, TileScale, 0.2));
				Obj->SetGridPosition(x, y);
				TileArray.Add(Obj);
				TileMap.Add(FVector2D(x, y), Obj);

			}
			
			
		}
	}
}

void AGameField::GeneratePieces()
{

	for (int32 x = 0; x < Size; x++)
	{
		for (int32 y = 0; y < Size; y++)
		{
			
			
			if (x == 1)
			{
				FVector Location = AGameField::GetRelativeLocationByXYPosition(x, y);
				ABasePiece* Obj = GetWorld()->SpawnActor<ABasePiece>(WPawnClass, Location, FRotator::ZeroRotator);
				//UMaterialInterface* Material = LoadObject<UMaterialInterface>(nullptr, TEXT("/Game/Materials/M_Marker_3"));
				//Obj->SetMaterial(Material);
				const float TileScale = TileSize / 100;
				Obj->SetActorScale3D(FVector(TileScale, TileScale, 0.3));
				Obj->SetPiecePosition(x, y);
				Obj->SetPieceColor(EPieceColor::WHITE);
				Obj->SetPieceType(EPieceType::PAWN);
				FVector2D PieceLocation = Obj->GetGridPosition();
				ATile* Tile = GetTileByLocation(PieceLocation);
				Tile->SetOccupyingChessPiece(Obj);
				PieceArray.Add(Obj);
				PieceMap.Add(FVector2D(x, y), Obj);
			}
			else if (x == 6) 
				{
					FVector Location = AGameField::GetRelativeLocationByXYPosition(x, y);
					ABasePiece* Obj = GetWorld()->SpawnActor<ABasePiece>(BPawnClass, Location, FRotator::ZeroRotator);
					const float TileScale = TileSize / 100;
					Obj->SetActorScale3D(FVector(TileScale, TileScale, 0.3));
					Obj->SetPiecePosition(x, y);
					Obj->SetPieceColor(EPieceColor::BLACK);
					Obj->SetPieceType(EPieceType::PAWN);
					FVector2D PieceLocation = Obj->GetGridPosition();
					ATile* Tile = GetTileByLocation(PieceLocation);
					Tile->SetOccupyingChessPiece(Obj); 
					PieceArray.Add(Obj);
					PieceMap.Add(FVector2D(x, y), Obj);
				}
			
			else if (x == 0)
			{
				if (y == 0) 
				{
					FVector Location = AGameField::GetRelativeLocationByXYPosition(x, y);
					ABasePiece* Obj = GetWorld()->SpawnActor<ABasePiece>(WRookClass, Location, FRotator::ZeroRotator);
					const float TileScale = TileSize / 100;
					Obj->SetActorScale3D(FVector(TileScale, TileScale, 0.3));
					Obj->SetPiecePosition(x, y);
					Obj->SetPieceColor(EPieceColor::WHITE);
					Obj->SetPieceType(EPieceType::ROOK);
					FVector2D PieceLocation = Obj->GetGridPosition();
					ATile* Tile = GetTileByLocation(PieceLocation);
					Tile->SetOccupyingChessPiece(Obj);
					PieceArray.Add(Obj);
					PieceMap.Add(FVector2D(x, y), Obj);
				}

				else if (y == 7) 
				{
					FVector Location = AGameField::GetRelativeLocationByXYPosition(x, y);
					ABasePiece* Obj = GetWorld()->SpawnActor<ABasePiece>(WRookClass, Location, FRotator::ZeroRotator);
					const float TileScale = TileSize / 100;
					Obj->SetActorScale3D(FVector(TileScale, TileScale, 0.3));
					Obj->SetPiecePosition(x, y);
					Obj->SetPieceColor(EPieceColor::WHITE);
					Obj->SetPieceType(EPieceType::ROOK);
					FVector2D PieceLocation = Obj->GetGridPosition();
					ATile* Tile = GetTileByLocation(PieceLocation);
					Tile->SetOccupyingChessPiece(Obj);
					PieceArray.Add(Obj);
					PieceMap.Add(FVector2D(x, y), Obj);
				}

				else if (y == 1 || y == 6) 
				{
					FVector Location = AGameField::GetRelativeLocationByXYPosition(x, y);
					ABasePiece* Obj = GetWorld()->SpawnActor<ABasePiece>(WKnightClass, Location, FRotator::ZeroRotator);
					const float TileScale = TileSize / 100;
					Obj->SetActorScale3D(FVector(TileScale, TileScale, 0.3));
					Obj->SetPiecePosition(x, y);
					Obj->SetPieceColor(EPieceColor::WHITE);
					Obj->SetPieceType(EPieceType::KNIGHT);
					FVector2D PieceLocation = Obj->GetGridPosition();
					ATile* Tile = GetTileByLocation(PieceLocation);
					Tile->SetOccupyingChessPiece(Obj);
					PieceArray.Add(Obj);
					PieceMap.Add(FVector2D(x, y), Obj);
				}
				else if (y == 2 || y==5) 
				{
					FVector Location = AGameField::GetRelativeLocationByXYPosition(x, y);
					ABasePiece* Obj = GetWorld()->SpawnActor<ABasePiece>(WBishopClass, Location, FRotator::ZeroRotator);
					const float TileScale = TileSize / 100;
					Obj->SetActorScale3D(FVector(TileScale, TileScale, 0.3));
					Obj->SetPiecePosition(x, y);
					Obj->SetPieceColor(EPieceColor::WHITE);
					Obj->SetPieceType(EPieceType::BISHOP);
					FVector2D PieceLocation = Obj->GetGridPosition();
					ATile* Tile = GetTileByLocation(PieceLocation);
					Tile->SetOccupyingChessPiece(Obj);
					PieceArray.Add(Obj);
					PieceMap.Add(FVector2D(x, y), Obj);
				}

				else if (y == 3) 
				{
					FVector Location = AGameField::GetRelativeLocationByXYPosition(x, y);
					ABasePiece* Obj = GetWorld()->SpawnActor<ABasePiece>(WQueenClass, Location, FRotator::ZeroRotator);
					const float TileScale = TileSize / 100;
					Obj->SetActorScale3D(FVector(TileScale, TileScale, 0.3));
					Obj->SetPiecePosition(x, y);
					Obj->SetPieceColor(EPieceColor::WHITE);
					Obj->SetPieceType(EPieceType::QUEEN);
					FVector2D PieceLocation = Obj->GetGridPosition();
					ATile* Tile = GetTileByLocation(PieceLocation);
					Tile->SetOccupyingChessPiece(Obj);
					PieceArray.Add(Obj);
					PieceMap.Add(FVector2D(x, y), Obj);
				}

				else if (y == 4) 
				{
					FVector Location = AGameField::GetRelativeLocationByXYPosition(x, y);
					ABasePiece* Obj = GetWorld()->SpawnActor<ABasePiece>(WKingClass, Location, FRotator::ZeroRotator);
					const float TileScale = TileSize / 100;
					Obj->SetActorScale3D(FVector(TileScale, TileScale, 0.3));
					Obj->SetPiecePosition(x, y);
					Obj->SetPieceColor(EPieceColor::WHITE);
					Obj->SetPieceType(EPieceType::KING);
					FVector2D PieceLocation = Obj->GetGridPosition();
					ATile* Tile = GetTileByLocation(PieceLocation);
					Tile->SetOccupyingChessPiece(Obj);
					PieceArray.Add(Obj);
					PieceMap.Add(FVector2D(x, y), Obj);
					WhiteKing = Obj;
				}


			}

			
			else if (x == 7)
			{
				if (y == 0 || y == 7) 
				{
					FVector Location = AGameField::GetRelativeLocationByXYPosition(x, y);
					ABasePiece* Obj = GetWorld()->SpawnActor<ABasePiece>(BRookClass, Location, FRotator::ZeroRotator);
					const float TileScale = TileSize / 100;
					Obj->SetActorScale3D(FVector(TileScale, TileScale, 0.3));
					Obj->SetPiecePosition(x, y);
					Obj->SetPieceColor(EPieceColor::BLACK);
					Obj->SetPieceType(EPieceType::ROOK);
					FVector2D PieceLocation = Obj->GetGridPosition();
					ATile* Tile = GetTileByLocation(PieceLocation);
					Tile->SetOccupyingChessPiece(Obj);
					PieceArray.Add(Obj);
					PieceMap.Add(FVector2D(x, y), Obj);
				}

				else if (y == 1 || y == 6) 
				{
					FVector Location = AGameField::GetRelativeLocationByXYPosition(x, y);
					ABasePiece* Obj = GetWorld()->SpawnActor<ABasePiece>(BKnightClass, Location, FRotator::ZeroRotator);
					const float TileScale = TileSize / 100;
					Obj->SetActorScale3D(FVector(TileScale, TileScale, 0.3));
					Obj->SetPiecePosition(x, y);
					Obj->SetPieceColor(EPieceColor::BLACK);
					Obj->SetPieceType(EPieceType::KNIGHT);
					FVector2D PieceLocation = Obj->GetGridPosition();
					ATile* Tile = GetTileByLocation(PieceLocation);
					Tile->SetOccupyingChessPiece(Obj);
					PieceArray.Add(Obj);
					PieceMap.Add(FVector2D(x, y), Obj);
				}
				else if (y == 2 || y == 5) 
				{
					FVector Location = AGameField::GetRelativeLocationByXYPosition(x, y);
					ABasePiece* Obj = GetWorld()->SpawnActor<ABasePiece>(BBishopClass, Location, FRotator::ZeroRotator);
					const float TileScale = TileSize / 100;
					Obj->SetActorScale3D(FVector(TileScale, TileScale, 0.3));
					Obj->SetPiecePosition(x, y);
					Obj->SetPieceColor(EPieceColor::BLACK);
					Obj->SetPieceType(EPieceType::BISHOP);
					FVector2D PieceLocation = Obj->GetGridPosition();
					ATile* Tile = GetTileByLocation(PieceLocation);
					Tile->SetOccupyingChessPiece(Obj);
					PieceArray.Add(Obj);
					PieceMap.Add(FVector2D(x, y), Obj);
				}

				else if (y == 3) 
				{
					FVector Location = AGameField::GetRelativeLocationByXYPosition(x, y);
					ABasePiece* Obj = GetWorld()->SpawnActor<ABasePiece>(BQueenClass, Location, FRotator::ZeroRotator);
					const float TileScale = TileSize / 100;
					Obj->SetActorScale3D(FVector(TileScale, TileScale, 0.3));
					Obj->SetPiecePosition(x, y);
					Obj->SetPieceColor(EPieceColor::BLACK);
					Obj->SetPieceType(EPieceType::QUEEN);
					FVector2D PieceLocation = Obj->GetGridPosition();
					ATile* Tile = GetTileByLocation(PieceLocation);
					Tile->SetOccupyingChessPiece(Obj);
					PieceArray.Add(Obj);
					PieceMap.Add(FVector2D(x, y), Obj);
				}

				else if (y == 4) 
				{
					FVector Location = AGameField::GetRelativeLocationByXYPosition(x, y);
					ABasePiece* Obj = GetWorld()->SpawnActor<ABasePiece>(BKingClass, Location, FRotator::ZeroRotator);
					const float TileScale = TileSize / 100;
					Obj->SetActorScale3D(FVector(TileScale, TileScale, 0.3));
					Obj->SetPiecePosition(x, y);
					Obj->SetPieceColor(EPieceColor::BLACK);
					Obj->SetPieceType(EPieceType::KING);
					FVector2D PieceLocation = Obj->GetGridPosition();
					ATile* Tile = GetTileByLocation(PieceLocation);
					Tile->SetOccupyingChessPiece(Obj);
					PieceArray.Add(Obj);
					PieceMap.Add(FVector2D(x, y), Obj);
					BlackKing = Obj;
				}


			}
		}
	}

	
}

void AGameField::ResetTilesColor()
{
	for (auto& position : PossibleMoves) 
	{
		position->SetMaterial(4);
	}
	ResetPossibleMoves();
}

void AGameField::ResetGa()
{
	
		UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
}

FVector2D AGameField::GetPosition(const FHitResult& Hit)
{
	return Cast<ATile>(Hit.GetActor())->GetGridPosition();
}

TArray<ATile*>& AGameField::GetTileArray()
{
	return TileArray;
}

TArray<ATile*>& AGameField::GetPossibleMovesTileArray()
{
	return PossibleMoves;
}

TArray<ABasePiece*>& AGameField::GetPieceArray()
{
	return PieceArray;
}




FVector AGameField::GetRelativeLocationByXYPosition(const int32 InX, const int32 InY) const
{
	return TileSize * FVector(InX, InY, 0);
}



FVector2D AGameField::GetXYPositionByRelativeLocation(const FVector& Location) const
{
	const double x = Location[0] / (TileSize );
	const double y = Location[1] / (TileSize );
	// GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, FString::Printf(TEXT("x=%f,y=%f"), x, y));
	return FVector2D(x, y);
}


ATile* AGameField::GetTileByLocation(const FVector2D& Location) const
{
	for (ATile* Tile : TileArray)
	{
		if (Tile && Tile->GetGridPosition() == Location)
		{
			return Tile;
		}
	}

	return nullptr;
}


void AGameField::ResetPossibleMoves()
{
	PossibleMoves.Empty();
}



// Called every frame
//void AGameField::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}

