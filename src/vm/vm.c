#include "vm.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define STACK_MAX 1024
#define VAR_MAX   256

/* Stack */
static int stack[STACK_MAX];
static int sp = 0;

/* Variable table */
typedef struct {
    char name[32];
    int value;
} Variable;

static Variable vars[VAR_MAX];
static int var_count = 0;

/* ---------------- Stack helpers ---------------- */

static void push(int value) {
    if (sp >= STACK_MAX) {
        fprintf(stderr, "VM error: stack overflow\n");
        exit(1);
    }
    stack[sp++] = value;
}

static int pop(void) {
    if (sp <= 0) {
        fprintf(stderr, "VM error: stack underflow\n");
        exit(1);
    }
    return stack[--sp];
}

/* ---------------- Variable helpers ---------------- */

static int find_var(const char *name) {
    for (int i = 0; i < var_count; i++) {
        if (strcmp(vars[i].name, name) == 0)
            return i;
    }
    return -1;
}

static void store_var(const char *name, int value) {
    int idx = find_var(name);
    if (idx >= 0) {
        vars[idx].value = value;
    } else {
        if (var_count >= VAR_MAX) {
            fprintf(stderr, "VM error: too many variables\n");
            exit(1);
        }
        strncpy(vars[var_count].name, name, 31);
        vars[var_count].name[31] = '\0';
        vars[var_count].value = value;
        var_count++;
    }
}

static int load_var(const char *name) {
    int idx = find_var(name);
    if (idx < 0) {
        fprintf(stderr, "VM error: undefined variable '%s'\n", name);
        exit(1);
    }
    return vars[idx].value;
}

/* ---------------- VM execution ---------------- */

void vm_execute(void) {
    char instr[32];

    while (scanf("%31s", instr) == 1) {

        /* PUSH <number> */
        if (strcmp(instr, "PUSH") == 0) {
            int value;
            scanf("%d", &value);
            push(value);
        }

        /* LOAD <name> */
        else if (strcmp(instr, "LOAD") == 0) {
            char name[32];
            scanf("%31s", name);
            push(load_var(name));
        }

        /* STORE <name> */
        else if (strcmp(instr, "STORE") == 0) {
            char name[32];
            scanf("%31s", name);
            int value = pop();
            store_var(name, value);
        }

        /* Arithmetic ops */
        else if (strcmp(instr, "ADD") == 0) {
            int b = pop();
            int a = pop();
            push(a + b);
        }
        else if (strcmp(instr, "SUB") == 0) {
            int b = pop();
            int a = pop();
            push(a - b);
        }
        else if (strcmp(instr, "MUL") == 0) {
            int b = pop();
            int a = pop();
            push(a * b);
        }
        else if (strcmp(instr, "DIV") == 0) {
            int b = pop();
            int a = pop();
            push(a / b);
        }

        else {
            fprintf(stderr, "VM error: unknown instruction '%s'\n", instr);
            exit(1);
        }
    }

    /* Optional: print final variables */
    printf("\n=== VM STATE ===\n");
    for (int i = 0; i < var_count; i++) {
        printf("%s = %d\n", vars[i].name, vars[i].value);
    }
}
