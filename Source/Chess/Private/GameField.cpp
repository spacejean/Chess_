// Fill out your copyright notice in the Description page of Project Settings.
//TODO cambiare TileScale per PieceScale

#include "GameField.h"
#include "Kismet/GameplayStatics.h"
#include "BaseSign.h"
#include "Chess_GameMode.h"

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
	//NONVA
	// tile padding dimension
	CellPadding = 20;


}


// Called when the game starts or when spawned
void AGameField::BeginPlay()
{
	Super::BeginPlay();
	GenerateField();
	GeneratePieces();
}

/*
void AGameField::ResetField()
{
	for (ATile* Obj : TileArray)
	{
		Obj->SetTileStatus(NOT_ASSIGNED, ETileStatus::EMPTY);
	}

	// send broadcast event to registered objects 
	OnResetEvent.Broadcast();

	AChess_GameMode* GameMode = Cast<AChess_GameMode>(GetWorld()->GetAuthGameMode());
	GameMode->IsGameOver = false;
	GameMode->MoveCounter = 0;
	GameMode->ChoosePlayerAndStartGame();
}

*/


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
					//UMaterialInterface* Material = LoadObject<UMaterialInterface>(nullptr, TEXT("/Game/Materials/M_Marker_3"));
					//Obj->SetMaterial(Material);
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
					//UMaterialInterface* Material = LoadObject<UMaterialInterface>(nullptr, TEXT("/Game/Materials/M_Marker_3"));
					//Obj->SetMaterial(Material);
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
					//UMaterialInterface* Material = LoadObject<UMaterialInterface>(nullptr, TEXT("/Game/Materials/M_Marker_3"));
					//Obj->SetMaterial(Material);
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
					//UMaterialInterface* Material = LoadObject<UMaterialInterface>(nullptr, TEXT("/Game/Materials/M_Marker_3"));
					//Obj->SetMaterial(Material);
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
					//UMaterialInterface* Material = LoadObject<UMaterialInterface>(nullptr, TEXT("/Game/Materials/M_Marker_3"));
					//Obj->SetMaterial(Material);
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
					//UMaterialInterface* Material = LoadObject<UMaterialInterface>(nullptr, TEXT("/Game/Materials/M_Marker_3"));
					//Obj->SetMaterial(Material);
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
					//UMaterialInterface* Material = LoadObject<UMaterialInterface>(nullptr, TEXT("/Game/Materials/M_Marker_3"));
					//Obj->SetMaterial(Material);
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
				}


			}

			
			else if (x == 7)
			{
				if (y == 0 || y == 7) 
				{
					FVector Location = AGameField::GetRelativeLocationByXYPosition(x, y);
					ABasePiece* Obj = GetWorld()->SpawnActor<ABasePiece>(BRookClass, Location, FRotator::ZeroRotator);
					//UMaterialInterface* Material = LoadObject<UMaterialInterface>(nullptr, TEXT("/Game/Materials/M_Marker_3"));
					//Obj->SetMaterial(Material);
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
					//UMaterialInterface* Material = LoadObject<UMaterialInterface>(nullptr, TEXT("/Game/Materials/M_Marker_3"));
					//Obj->SetMaterial(Material);
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
					//UMaterialInterface* Material = LoadObject<UMaterialInterface>(nullptr, TEXT("/Game/Materials/M_Marker_3"));
					//Obj->SetMaterial(Material);
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
					//UMaterialInterface* Material = LoadObject<UMaterialInterface>(nullptr, TEXT("/Game/Materials/M_Marker_3"));
					//Obj->SetMaterial(Material);
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
					//UMaterialInterface* Material = LoadObject<UMaterialInterface>(nullptr, TEXT("/Game/Materials/M_Marker_3"));
					//Obj->SetMaterial(Material);
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


bool AGameField::IsWinPosition(const FVector2D Position) const
{
	const int32 Offset = WinSize - 1;
	// vertical lines
	for (int32 i = Position[0] - Offset; i <= Position[0]; i++)
	{
		if (IsWinLine(FVector2D(i, Position[1]), FVector2D(i + Offset, Position[1])))
		{
			return true;
		}
	}

	// horizontal lines
	for (int32 i = Position[1] - Offset; i <= Position[1]; i++)
	{
		if (IsWinLine(FVector2D(Position[0], i), FVector2D(Position[0], i + Offset)))
		{
			return true;
		}
	}

	// diagonal lines
	for (int32 i = -Offset; i <= 0; i++)
	{
		if (IsWinLine(FVector2D(Position[0] + i, Position[1] + i), FVector2D(Position[0] + Offset + i, Position[1] + Offset + i)))
		{
			return true;
		}
		if (IsWinLine(FVector2D(Position[0] + i, Position[1] - i), FVector2D(Position[0] + Offset + i, Position[1] - Offset - i)))
		{
			return true;
		}
	}

	return false;
}

inline bool AGameField::IsWinLine(const FVector2D Begin, const FVector2D End) const
{
	return IsValidPosition(Begin) && IsValidPosition(End) && AllEqual(GetLine(Begin, End));
}

inline bool AGameField::IsValidPosition(const FVector2D Position) const
{
	return 0 <= Position[0] && Position[0] < Size && 0 <= Position[1] && Position[1] < Size;
}

TArray<int32> AGameField::GetLine(const FVector2D Begin, const FVector2D End) const
{
	int32 xSign;
	if (Begin[0] == End[0])
	{
		xSign = 0;
	}
	else
	{
		xSign = Begin[0] < End[0] ? 1 : -1;
	}

	int32 ySign;
	if (Begin[1] == End[1])
	{
		ySign = 0;
	}
	else
	{
		ySign = Begin[1] < End[1] ? 1 : -1;
	}

	TArray<int32> Line;
	int32 x = Begin[0] - xSign;
	int32 y = Begin[1] - ySign;
	do
	{
		x += xSign;
		y += ySign;
		Line.Add((TileMap[FVector2D(x, y)])->GetOwner());
	} while (x != End[0] || y != End[1]);

	return Line;
}

bool AGameField::AllEqual(const TArray<int32>& Array) const
{
	if (Array.Num() == 0)
	{
		return false;
	}
	const int32 Value = Array[0];

	if (Value == NOT_ASSIGNED)
	{
		return false;
	}

	for (int32 i = 1; i < Array.Num(); i++)
	{
		if (Value != Array[i])
		{
			return false;
		}
	}

	return true;
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

