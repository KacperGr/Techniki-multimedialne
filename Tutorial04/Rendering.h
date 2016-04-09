#pragma once

#include <windows.h>
#include <d3d11_1.h>
#include <d3dcompiler.h>
#include <directxmath.h>
#include <directxcolors.h>
#include "resource.h"
#include "Modul_Open_CL.h"

using namespace DirectX;
//--------------------------------------------------------------------------------------
//Struktury
//--------------------------------------------------------------------------------------
struct SimpleVertex
{
	XMFLOAT3 Pos;
	XMFLOAT4 Color;
};


struct ConstantBuffer
{
	XMMATRIX mWorld;
	XMMATRIX mView;
	XMMATRIX mProjection;
};

//--------------------------------------------------------------------------------------
//Deklaracje funkcji
//--------------------------------------------------------------------------------------
HRESULT InitDevice();
void CleanupDevice();
void Render();

extern HINSTANCE               g_hInst;
extern HWND                    g_hWnd;
extern D3D_DRIVER_TYPE         g_driverType;
extern D3D_FEATURE_LEVEL       g_featureLevel;
extern ID3D11Device*           g_pd3dDevice;
extern ID3D11Device1*          g_pd3dDevice1;
extern ID3D11DeviceContext*    g_pImmediateContext;
extern ID3D11DeviceContext1*   g_pImmediateContext1;
extern IDXGISwapChain*         g_pSwapChain;
extern IDXGISwapChain1*        g_pSwapChain1;
extern ID3D11RenderTargetView* g_pRenderTargetView;
extern ID3D11VertexShader*     g_pVertexShader;
extern ID3D11PixelShader*      g_pPixelShader;
extern ID3D11InputLayout*      g_pVertexLayout;
extern ID3D11Buffer*           g_pVertexBuffer;
extern ID3D11Buffer*           g_pIndexBuffer;
extern ID3D11Buffer*           g_pConstantBuffer;
extern XMMATRIX                g_World;
extern XMMATRIX                g_View;
extern XMMATRIX                g_Projection;
