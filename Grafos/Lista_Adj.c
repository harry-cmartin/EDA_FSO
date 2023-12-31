
typedef struct no *p_no;

struct no {
    int v;
    p_no prox;
};

typedef struct grafo *p_grafo;

struct grafo {
    p_no *adjacencia;
    int n;
};

p_grafo criar_grafo(int n) {
    int i;
    p_grafo g = malloc(sizeof(struct grafo));
    g->n = n;
    g->adjacencia = malloc(n * sizeof(p_no));

        for (i = 0; i < n; i++)
            g->adjacencia[i] = NULL;

    return g;
}

void libera_lista(p_no lista) {
    
    if (lista != NULL) {
        libera_lista(lista->prox);
        free(lista);
    }
}

void destroi_grafo(p_grafo g) {

    int i;

    for (i = 0; i < g->n; i++)
        libera_lista(g->adjacencia[i]);
        free(g->adjacencia);
    free(g);
} 

p_no insere_na_lista(p_no lista, int v) {

    p_no novo = malloc(sizeof(struct no));
    novo->v = v;
    novo->prox = lista;
    
    return novo;

}

void insere_aresta(p_grafo g, int u, int v) {
    g->adjacencia[v] = insere_na_lista(g->adjacencia[v], u);
    g->adjacencia[u] = insere_na_lista(g->adjacencia[u], v);
}


p_no remove_da_lista(p_no lista, int v) {

    p_no proximo;

    if (lista == NULL)
        return NULL;
    else if (lista->v == v) {
        proximo = lista->prox;
        free(lista);

        return proximo;
    } else {

    lista->prox = remove_da_lista(lista->prox, v);

    return lista;
    }
}
 
void remove_aresta(p_grafo g, int u, int v) {
    g->adjacencia[u] = remove_da_lista(g->adjacencia[u], v);
    g->adjacencia[v] = remove_da_lista(g->adjacencia[v], u);
}


int tem_aresta(p_grafo g, int u, int v) {

    p_no t;

    for (t = g->adjacencia[u]; t != NULL; t = t->prox)
        if (t->v == v)
            return 1;

    return 0;
}

void imprime_arestas(p_grafo g) {

    int u;
    p_no t;
    
    for (u = 0; u < g->n; u++)
        for (t = g->adjacencia[u]; t != NULL; t = t->prox)
            printf("{%d,%d}\n", u, t->v);
}
