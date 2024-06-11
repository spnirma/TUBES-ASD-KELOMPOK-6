#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Mendefinisikan struktur film
typedef struct {
    int id;
    char title[100];
    int year;
    float rating;
} Movie;

// Mendefinisikan struktur node pohon
typedef struct TreeNode {
    Movie data;
    struct TreeNode* left;
    struct TreeNode* right;
} TreeNode;

// Prototipe fungsi
TreeNode* createNode(Movie data);
TreeNode* insert(TreeNode* root, Movie data);
TreeNode* search(TreeNode* root, int id);
void printMovie(Movie movie);
void inorder(TreeNode* root);
void preorder(TreeNode* root);
void postorder(TreeNode* root);

// Fungsi untuk membuat node baru
TreeNode* createNode(Movie data) {
    TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Fungsi untuk menambahkan film ke pohon biner
TreeNode* insert(TreeNode* root, Movie data) {
    if (root == NULL) {
        return createNode(data);
    }
    if (data.id < root->data.id) {
        root->left = insert(root->left, data);
    } else {
        root->right = insert(root->right, data);
    }
    return root;
}

// Fungsi untuk mencari film berdasarkan ID
TreeNode* search(TreeNode* root, int id) {
    if (root == NULL || root->data.id == id) {
        return root;
    }
    if (id < root->data.id) {
        return search(root->left, id);
    } else {
        return search(root->right, id);
    }
}

// Fungsi untuk mencetak detail film
void printMovie(Movie movie) {
    printf("ID: %d\n", movie.id);
    printf("Judul: %s\n", movie.title);
    printf("Tahun: %d\n", movie.year);
    printf("Rating: %.2f\n", movie.rating);
}

// Traversal inorder untuk menampilkan film
void inorder(TreeNode* root) {
    if (root != NULL) {
        inorder(root->left);
        printMovie(root->data);
        inorder(root->right);
    }
}

// Traversal preorder untuk menampilkan film
void preorder(TreeNode* root) {
    if (root != NULL) {
        printMovie(root->data);
        preorder(root->left);
        preorder(root->right);
    }
}

// Traversal postorder untuk menampilkan film
void postorder(TreeNode* root) {
    if (root != NULL) {
        postorder(root->left);
        postorder(root->right);
        printMovie(root->data);
    }
}

// Fungsi utama dengan menu untuk pengguna
int main() {
    TreeNode* root = NULL;
    Movie movies[] = {
        {1, "The Shawshank Redemption", 1994, 9.3},
        {2, "The Godfather", 1972, 9.2},
        {3, "The Dark Knight", 2008, 9.0},
        {4, "12 Angry Men", 1957, 9.0},
        {5, "Schindler's List", 1993, 8.9}
    };
    int numMovies = sizeof(movies) / sizeof(movies[0]);

    // Menambahkan film secara otomatis
    for (int i = 0; i < numMovies; i++) {
        root = insert(root, movies[i]);
    }

    // Mencari film berdasarkan ID secara otomatis
    int searchIds[] = {1, 2, 6}; // ID film yang ingin dicari (termasuk ID yang tidak ada untuk pengujian)
    for (int i = 0; i < sizeof(searchIds) / sizeof(searchIds[0]); i++) {
        TreeNode* searchResult = search(root, searchIds[i]);
        if (searchResult != NULL) {
            printf("\nDetail Film dengan ID %d:\n", searchIds[i]);
            printMovie(searchResult->data);
        } else {
            printf("\nFilm dengan ID %d tidak ditemukan!\n", searchIds[i]);
        }
    }

    // Menampilkan semua film dalam urutan yang berbeda
    printf("\nMenampilkan semua film (In-order):\n");
    inorder(root);

    printf("\nMenampilkan semua film (Pre-order):\n");
    preorder(root);

    printf("\nMenampilkan semua film (Post-order):\n");
    postorder(root);

    printf("Keluar dari program.\n");
    return 0;
}
