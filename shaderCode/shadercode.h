#ifndef SHADERCODE
#define SHADERCODE
static const char * verShaderSourceCore =
        "#version 430 core\n"
        "layout (location = 0) in vec3 position\n;"
        "layout (location = 1) in vec3 normal;\n"
        "layout (location = 2) in vec2 texCoords"
        "out vec2 TexCoords;\n"
        "out vec3 fragPosition;\n"
        "out vec3 Normal;\n"
        "void main()\n"
        "{\n"
            "gl_Position = vec4(Position,1.0f);\n"

        "}\n";

static const char * conShaderSourceCore =
        "#version 430 core\n"
        "layout (vertices = 6) out;\n"
        "uniform float  Inner;\n"
        "uniform float  Outer;\n"
        "void main()\n"
        "{\n"
        "gl_TessLevelOuter[1] = 10;\n"
        "gl_TessLevelOuter[3] = 10;\n"
        "gl_out[gl_InvocationID].gl_Position = \n"
        "gl_in[gl_InvocationID].gl_Position;\n"
        "}\n";

static const char * evalShaderSourceCore =
        "#version 430 core\n"
        "layout (quads, equal_spacing, ccw) in;"

        "uniform mat4  ROTATE0;\n"
        "uniform mat4  ROTATE1;\n"
        "uniform mat4  MV;\n"
        "uniform mat4  P\n;"
        "void main()\n"
        "{\n"
            "vec4  pos = vec4( 0.0 );\n"
            "float  u = gl_TessCoord.x;\n"
            "float  v = gl_TessCoord.y;\n"
            "if(roundEven(v) == 0)\n"
            "{\n"
                "pos = gl_in[1].gl_Position;\n"
                "for(int i=0;i <= roundEven(u*10);i++)\n"
                "{\n"
                    "if(i>0)"
                    "pos = ROTATE1*pos;"
                "}\n"
            "}\n"
            "if(roundEven(v) == 1)\n"
            "{\n"
                "pos = gl_in[4].gl_Position;\n"
                "for(int i=0;i <= roundEven(u*10);i++)\n"
                "{\n"
                    "if(i>0)"
                    "pos = ROTATE1*pos;"
                "}\n"
            "}\n"

            "gl_Position = P * MV * pos;\n"
        "}\n";

#endif // SHADERCODE

