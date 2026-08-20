#version 330

in vec2 fragTexCoord;
in vec4 fragColor;

uniform sampler2D texture0;

uniform float time;
uniform vec2 resolution;

out vec4 finalColor;

float random(vec2 uv)
{
    return fract(
        sin(
            dot(
                uv,
                vec2(12.9898, 78.233)
            )
        ) * 43758.5453
    );
}

void main()
{
    vec2 uv = fragTexCoord;

    vec4 sceneColor =
        texture(texture0, uv);

    float noise =
        random(
            uv * resolution +
            time * 1000.0
        );

    noise =
        (noise - 0.5) * 0.18;

    vec3 color =
        sceneColor.rgb +
        noise;

    finalColor =
        vec4(
            color,
            sceneColor.a
        );
}