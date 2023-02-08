#ifdef GL_ES
precision mediump float;
#endif

uniform sampler2D texture0;
uniform vec2 u_resolution;

uniform vec4 u_rectangle;
uniform float u_roundness;
uniform vec4 u_windowTint;

float RBSDF(vec2 centerPosition, vec2 size, float radius)
{
    if (min(size.x, size.y) < radius)
        radius = min(size.x, size.y);
    return length(max(abs(centerPosition) - size + radius, 0.)) - radius;
}

void main()
{
    vec2 size = u_rectangle.zw / 2.;
    vec2 position = gl_FragCoord.xy - u_rectangle.xy - size;
    float rectangleRBSDF = smoothstep(1., 0., RBSDF(position, size, u_roundness));
    vec4 bgcolor = vec4(texture2D(texture0, gl_FragCoord.xy / u_resolution).rgb * rectangleRBSDF, rectangleRBSDF);
    vec4 tint = vec4(u_windowTint.rgb * u_windowTint.a, u_windowTint.a);
    gl_FragColor = bgcolor * (1. - tint.a) + tint * rectangleRBSDF;
}
