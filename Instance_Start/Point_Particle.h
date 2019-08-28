#pragma once
#include "David_Particle_Instancing.h"

struct David_Particle_Vertex
{
	D3DXVECTOR3  vPosition;
	D3DXVECTOR3  vVel;
	float						Timer;
	unsigned int			Type;
};

struct Constant_buffer_for_Particle
{
	D3DXMATRIX    Matrixs_World_View_Proj;
	D3DXMATRIX    Matrix_Inverse_View;
	D3DXVECTOR4	  Gravity_each_Frame;

	float		  Global_Time;
	float		  Elapsed_Time;
	float		  Seconds_Per_Firework;

	float		  the_Number_of_Ember1_s;
	float		  Max_Number_Ember2_s;

	float		  m_py;
	float		  m_pz;
	float		  m_pw;
};



class Point_Particle : public David_Shape
{

public:
	ID3D11Buffer*		Buffer_Particle_Stream_To;
	ID3D11Buffer*		Buffer_Particle_Draw_From;

	ID3D11Texture1D*	Random_Texture_1D;
	ComPtr<ID3D11ShaderResourceView> Random_Texture1D_SRV;

	ID3D11VertexShader* VertexShader_Render_Particle;
	ID3D11VertexShader* VertexShader_Particle_Advancing;

	Constant_buffer_for_Particle	CB_Particle_Data;
	ComPtr<ID3D11Buffer>			Constant_Buffer;
	
	bool				Decisive_First;
	
	ComPtr<ID3D11GeometryShader> GS_Particle_Advancing;
	ComPtr<ID3D11GeometryShader> GS_Stream_Output;
	ComPtr<ID3D11VertexShader>	     VertexShader_Pass_Through;

public:
	virtual HRESULT CreateInputLayout();
	virtual HRESULT CreateVertexBuffer();
	virtual HRESULT CreateConstantBuffer();
	virtual HRESULT LoadShaderFile(ID3D11Device* pDevice, const TCHAR* pShaderFile);

public:

	virtual bool	Init();
	virtual bool	Frame(ID3D11DeviceContext* pContext, float fElapsedTime, float fSecPerFrame);
	virtual bool	Render(ID3D11DeviceContext* pImContext);

	HRESULT virtual CreateResource();

public:
	// This helper function creates a 1D texture full of random vectors. 
	// The shader suses the current time value to index into this texture to get a random vector.

	HRESULT virtual CreateRandomTexture_1D_SRV(ID3D11Device* pDevice);

	virtual bool	Particle_Advancing(ID3D11DeviceContext* pImContext, float Global_Time_in, float fSecPerFrame_in, D3DXVECTOR3 Gravity_in);

public:
	Point_Particle();
	virtual ~Point_Particle();
};
