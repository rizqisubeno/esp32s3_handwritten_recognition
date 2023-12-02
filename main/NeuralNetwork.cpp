#include "model_data.h"
#include "model_data2.h"
#include "tensorflow/lite/micro/micro_mutable_op_resolver.h"
#include "tensorflow/lite/micro/system_setup.h"
#include "tensorflow/lite/micro/micro_interpreter.h"
#include "tensorflow/lite/schema/schema_generated.h"
#include "NeuralNetwork.h"

const char *nn_model[] = {
    "cnn+mlp",
    "mlp only"
};

namespace{
    tflite::Model *model1 = nullptr;
    tflite::MicroInterpreter *interpreter1 = nullptr;
    TfLiteTensor *input1 = nullptr;
    TfLiteTensor *output1 = nullptr;

    constexpr int kTensorArenaSize = 20*1024;
    uint8_t tensor_arena1[kTensorArenaSize];

    tflite::Model *model2 = nullptr;
    tflite::MicroInterpreter *interpreter2 = nullptr;
    TfLiteTensor *input2 = nullptr;
    TfLiteTensor *output2 = nullptr;

    uint8_t tensor_arena2[kTensorArenaSize];
 
    template <unsigned int tOpCount> 
    class MicroMutableOpResolver;
    class Model;
    class MicroInterpreter;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////// FOR MODEL 1 TFLITE MICRO //////////////////////////////////////
extern "C" void nn_init1()
{
    model1 = const_cast<tflite::Model*>(tflite::GetModel(mnist_tflite));

    if(model1->version() != TFLITE_SCHEMA_VERSION){
        MicroPrintf("Model provided is schema version %d not equal to supported "
            "version %d.", model1->version(), TFLITE_SCHEMA_VERSION);
        return;
    }

    // Pull in only the operation implementations we need.
    static tflite::MicroMutableOpResolver<6> resolver1;
    if (resolver1.AddAdd() != kTfLiteOk)
    {
        return;
    }
    if (resolver1.AddConv2D() != kTfLiteOk)
    {
        return;
    }
    if (resolver1.AddMean() != kTfLiteOk)
    {
        return;
    }
    if (resolver1.AddFullyConnected() != kTfLiteOk){
        return;
    }
    if (resolver1.AddReshape() != kTfLiteOk){
        return;
    }
    if (resolver1.AddSoftmax() != kTfLiteOk){
        return;
    }

    // Build an interpreter to run the model with.
    static tflite::MicroInterpreter static_interpreter1(
        model1, resolver1, tensor_arena1, kTensorArenaSize);
    interpreter1 = &static_interpreter1;

    // Allocate memory from the tensor_arena for the model's tensors.
    TfLiteStatus allocate_status = interpreter1->AllocateTensors();
    if (allocate_status != kTfLiteOk) {
        MicroPrintf("AllocateTensors() failed");
        return;
    }

    size_t used_bytes = interpreter1->arena_used_bytes();
    MicroPrintf("Used bytes %d\n", used_bytes);

    // Obtain pointers to the model's input and output tensors.
    input1 = interpreter1->input(0);
    output1 = interpreter1->output(0);
}

// for inserting input image
extern "C" float *getInputBuffer1()
{
    return input1->data.f;
}

// get output from inference model 1
extern "C" float *predict1()
{
    interpreter1->Invoke();
    return output1->data.f;
}
////////////////////////////////////// FOR MODEL 1 TFLITE MICRO //////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////// FOR MODEL 2 TFLITE MICRO //////////////////////////////////////
extern "C" void nn_init2()
{
    //load the model 2 from flash
    model2 = const_cast<tflite::Model*>(tflite::GetModel(mnist_tflite2));

    // Check the schema version
    if(model2->version() != TFLITE_SCHEMA_VERSION){
        MicroPrintf("Model provided is schema version %d not equal to supported "
            "version %d.", model2->version(), TFLITE_SCHEMA_VERSION);
        return;
    }


    if(model2->version() != TFLITE_SCHEMA_VERSION){
        MicroPrintf("Model provided is schema version %d not equal to supported "
            "version %d.", model2->version(), TFLITE_SCHEMA_VERSION);
        return;
    }

    // Resolve operation implementations
    // Pull in only the operation implementations we need.
    static tflite::MicroMutableOpResolver<3> resolver2;
    if (resolver2.AddFullyConnected() != kTfLiteOk){
        return;
    }
    if (resolver2.AddReshape() != kTfLiteOk){
        return;
    }
    if (resolver2.AddSoftmax() != kTfLiteOk){
        return;
    }

    // Build an interpreter to run the model with.
    static tflite::MicroInterpreter static_interpreter2(
        model2, resolver2, tensor_arena2, kTensorArenaSize);
    interpreter2 = &static_interpreter2;

    // Allocate memory from the tensor_arena for the model's tensors.
    TfLiteStatus allocate_status = interpreter2->AllocateTensors();
    if (allocate_status != kTfLiteOk) {
        MicroPrintf("AllocateTensors() failed");
        return;
    }

    size_t used_bytes = interpreter2->arena_used_bytes();
    MicroPrintf("Used bytes %d\n", used_bytes);

    // Obtain pointers to the model's input and output tensors.
    input2 = interpreter2->input(0);
    output2 = interpreter2->output(0);
}

// for inserting input image
extern "C" float *getInputBuffer2()
{
    return input2->data.f;
}

// get output from inference model 2
extern "C" float *predict2()
{
    interpreter2->Invoke();
    return output2->data.f;
}
////////////////////////////////////// FOR MODEL 2 TFLITE MICRO //////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////

