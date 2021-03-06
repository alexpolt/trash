//amazing cubes
//vertex shader

bool noaa : register(b0);

sampler tex0 : register(s0);
sampler tex1 : register(s1);

static const float pi2 = 2*3.1415926;

float4 main( float2 screenxy : TEXCOORD0 ) : COLOR0 {

  float4 color0 = tex2D( tex0, screenxy );
  float2 dfaa = tex2D( tex1, screenxy ).xy;
  float area = dfaa.y;
  //decode direction
  float2 dir = float2( cos( dfaa.x * pi2 ), sin( dfaa.x * pi2 ) );
  float2 sdx = ddx( screenxy );
  float2 sdy = ddy( screenxy );

  if( noaa ) return float4( color0.rgb, 1 );

  float4 color1 = color0;

  //only do fetch if necessary (edge pixels)
  if( area > 0 && area < 1 ) 
    color1 = tex2D(tex0, screenxy + sdx*dir.x + sdy*dir.y );

  float4 color = lerp( color1, color0, area );
 
  return float4( color.rgb, 1 );
}

