#include "stdafx.h"
#include "Grid.h"
#include "LineRenderer.h"

Grid::Grid(Context * context)
	: context(context)
	, width(0)
	, height(0)
	, spacing(0)
{
	lineRenderer = new LineRenderer(context);
}

Grid::~Grid()
{
	SAFE_DELETE(lineRenderer);
}

void Grid::Create(const int & w, const int & h, const int & s, const D3DXCOLOR & color)
{
	width = (w % s) == 0 ? w : w - (w % s);
	height = (h % s) == 0 ? h : h - (h % s);
	spacing = s;

	//Vertical
	for (int i = 0; i <= width; i += spacing)
		lineRenderer->AddLine
		(
			Vector3(static_cast<float>(i), static_cast<float>(0), 0.0f),
			Vector3(static_cast<float>(i), static_cast<float>(height), 0.0f),
			color
		);
	
	//Horizontal
	for (int i = 0; i <= height; i += spacing)
		lineRenderer->AddLine
		(
			Vector3(static_cast<float>(0), static_cast<float>(i), 0.0f),
			Vector3(static_cast<float>(width), static_cast<float>(i), 0.0f),
			color
		);
}

void Grid::Update()
{
	lineRenderer->Update();
}

void Grid::Render()
{
	lineRenderer->Render();
}
