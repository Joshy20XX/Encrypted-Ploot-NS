#include "startmenu.h"
#include "./ui_startmenu.h"
#include <QFileDialog>
#include <QFile>
#include <QCoreApplication>
#include <QTextStream>
#include <QString>
#include "base64.hpp"  //Included Base64 library from tobiasbaker: https://github.com/tobiaslocker/base64
#include <QHash>
#include <QChar>
#include <QByteArray>
#include <QStringList>
#include <QtMath>

//PERMUATATION TABLES

//Initial Permuation Table
static QVector<int> initial_perm = {58, 50, 42, 34, 26, 18, 10, 2,
                                    60, 52, 44, 36, 28, 20, 12, 4,
                                    62, 54, 46, 38, 30, 22, 14, 6,
                                    64, 56, 48, 40, 32, 24, 16, 8,
                                    57, 49, 41, 33, 25, 17, 9, 1,
                                    59, 51, 43, 35, 27, 19, 11, 3,
                                    61, 53, 45, 37, 29, 21, 13, 5,
                                    63, 55, 47, 39, 31, 23, 15, 7 };

//Expansion d-table
static QVector<int> exp_d = {32, 1, 2, 3, 4, 5, 4, 5,
                             6, 7, 8, 9, 8, 9, 10, 11,
                             12, 13, 12, 13, 14, 15, 16, 17,
                             16, 17, 18, 19, 20, 21, 20, 21,
                             22, 23, 24, 25, 24, 25, 26, 27,
                             28, 29, 28, 29, 30, 31, 32, 1 };


//Straight Permuation Table
static QVector<int> per = {16, 7, 20, 21,
                           29, 12, 28, 17,
                           1, 15, 23, 26,
                           5, 18, 31, 10,
                           2, 8, 24, 14,
                           32, 27, 3, 9,
                           19, 13, 30, 6,
                           22, 11, 4, 25 };

// S-box Table
static QVector<QVector<QVector<int>>> sbox = {
    {
        {14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
        {0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
        {4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
        {15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}
    },

    {
        {15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10},
        {3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5},
        {0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15},
        {13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9}
    },

    {
        {10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8},
        {13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1},
        {13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7},
        {1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12}
    },

    {
        {7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15},
        {13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9},
        {10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4},
        {3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14}
    },

    {
        {2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9},
        {14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6},
        {4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14},
        {11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3}
    },

    {
        {12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11},
        {10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8},
        {9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6},
        {4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13}
    },

    {
        {4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1},
        {13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6},
        {1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2},
        {6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12}
    },

    {
        {13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7},
        {1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2},
        {7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8},
        {2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}

    }

};

//Final Permutation Table
static QVector<int> final_perm = {40, 8, 48, 16, 56, 24, 64, 32,
                                  39, 7, 47, 15, 55, 23, 63, 31,
                                  38, 6, 46, 14, 54, 22, 62, 30,
                                  37, 5, 45, 13, 53, 21, 61, 29,
                                  36, 4, 44, 12, 52, 20, 60, 28,
                                  35, 3, 43, 11, 51, 19, 59, 27,
                                  34, 2, 42, 10, 50, 18, 58, 26,
                                  33, 1, 41, 9, 49, 17, 57, 25};

//Parity bit drop table a.k.a. Permuted Choice 1 (PC-1)
static QVector<int> keyp = {57, 49, 41, 33, 25, 17, 9,
                            1, 58, 50, 42, 34, 26, 18,
                            10, 2, 59, 51, 43, 35, 27,
                            19, 11, 3, 60, 52, 44, 36,
                            63, 55, 47, 39, 31, 23, 15,
                            7, 62, 54, 46, 38, 30, 22,
                            14, 6, 61, 53, 45, 37, 29,
                            21, 13, 5, 28, 20, 12, 4};

//Number of bit shifts
static QVector<int> shift_table = {1, 1, 2, 2,
                                   2, 2, 2, 2,
                                   1, 2, 2, 2,
                                   2, 2, 2, 1};

//Compression of key from 56 bits to 48 bits
static QVector<int> key_comp = {14, 17, 11, 24, 1, 5,
                                3, 28, 15, 6, 21, 10,
                                23, 19, 12, 4, 26, 8,
                                16, 7, 27, 20, 13, 2,
                                41, 52, 31, 37, 47, 55,
                                30, 40, 51, 45, 33, 48,
                                44, 49, 39, 56, 34, 53,
                                46, 42, 50, 36, 29, 32};

//Added functions for DES encryption. Still a work-in-progress.
QString StartMenu::bin_to_hex(QString &string) {
    QString hex = "";

    //A lookup table for each binary value (4-bits) to its corresponding nybble.
    QHash<QString, QChar> binhex_map = {
        {"0000", '0'},
        {"0001", '1'},
        {"0010", '2'},
        {"0011", '3'},
        {"0100", '4'},
        {"0101", '5'},
        {"0110", '6'},
        {"0111", '7'},
        {"1000", '8'},
        {"1001", '9'},
        {"1010", 'A'},
        {"1011", 'B'},
        {"1100", 'C'},
        {"1101", 'D'},
        {"1110", 'E'},
        {"1111", 'F'}
    };
    for (int i=0; i < string.length(); i+=4) {

        //Take the bits, assemble it, and then append its corresponding nybble to the hex string.
        QString ch = "";
        ch += string[i];
        ch += string[i+1];
        ch += string[i+2];
        ch += string[i+3];
        hex += binhex_map[ch];
    }
    return hex;
}

QString StartMenu::hex_to_bin(QString &string) {
    QString bin = "";

    //A lookup table for the hex to bin conversion
    QHash<QChar, QString> hexbin_map = {
        {'0', "0000"},
        {'1', "0001"},
        {'2', "0010"},
        {'3', "0011"},
        {'4', "0100"},
        {'5', "0101"},
        {'6', "0110"},
        {'7', "0111"},
        {'8', "1000"},
        {'9', "1001"},
        {'A', "1010"},
        {'B', "1011"},
        {'C', "1100"},
        {'D', "1101"},
        {'E', "1110"},
        {'F', "1111"}
    };

    //For each nybble character in the hex string, append binary value to the binary string
    for (QChar i : string) {
        bin += hexbin_map[i];
    }
    return bin;
}

QString StartMenu::permute(QString &block, QVector<int> &arr, int n) {
    QString permutation = "";
    for (int i=0; i < n; i++) {
        permutation += block[arr[i] - 1];
    }
    return permutation;
}

QString StartMenu::shift_bit_left(QString &string, int n) {
    QString k = "";

    for (int i = n; i < string.length(); i++) k += string[i];
    for (int i = 0; i < n; i++) {
        k += string[i];
    }
    return k;
}

QString StartMenu::xor_add(QString &string1, QString &string2) {
    QString result = "";
    qDebug() << "Comparing:\n" << string1 << "\n" << string2;
    for (int j=0; j < string1.length(); j++) {
        if (string1[j] != string2[j]) {
            result += "1";
        } else {
            result += "0";
        }
    }
    return result;
}

QString StartMenu::dec_to_bin(int n) {
    QString bin = "";
    while (n > 0) {
        bin = (QChar)(n % 2 + '0') + bin;
        n /= 2;
    }
    while (bin.size() < 4) {
        bin = '0' + bin;
    }
    return bin;
}
int StartMenu::bin_to_dec(QString &string) {
    int decimal = 0, i = 0;

    for (QChar i : string) {
        decimal = (decimal << 1 | (i == '1'));
    }
    //qDebug() << "Decimal:" << decimal;

    return decimal;
}

//Convert hex to text
QString StartMenu::hex_to_char(QString &string) {
    QByteArray bytes = QByteArray::fromHex(string.toUtf8());
    QString result = QString::fromUtf8(bytes);

    return result;
}

//Keygen
void StartMenu::keygen(QString& key, QStringList &roundkeylist, QStringList &roundkeylist_bin) {
    QByteArray keyhex = key.toUtf8().toHex().toUpper();
    qDebug() << "Initial 64-bit Key (Hex): " << keyhex;
    QString key64 = keyhex;
    key64 = hex_to_bin(key64);
    qDebug() << "Initial 64-bit Key (Bin): " << key64;

    //Truncate the 64-bit key into 56-bits
    QString key56 = "";
    key56 = permute(key64, keyp, 56);

    //Get the left and right bits
    QString key_left = "", key_right = "";
    for (int i = 0; i < 28; i++) {
        key_left += key56[i];
    }

    for (int j=28; j < 56; j++) {
        key_right += key56[j];
    }
    qDebug() << "PC-1 key: " << key56 << "\nKey Left: " << key_left << "\nKey Right: " << key_right << "\n";

    //Shift the left and right halves of the key
    for (int i=0; i < 16; i++) {
        key_left = shift_bit_left(key_left, shift_table[i]);
        key_right = shift_bit_left(key_right, shift_table[i]);

        QString key56_combined = "";
        QString roundkey = "";

        //Combine the two halves into a 56-bit key and truncate to a 48-bit key
        key56_combined = key_left + key_right;
        roundkey = permute(key56_combined, key_comp, 48);

        //qDebug() << "Round key:" << i + 1 << roundkey;
        roundkeylist_bin.append(roundkey);

        roundkey = bin_to_hex(roundkey);
        roundkeylist.append(roundkey);
    }
}

//Encryption function with the chunk block, same or different key, and our round key lists
QString StartMenu::des_encrypt(QString &chunk_block, QStringList &roundkeylist, QStringList &roundkeylist_bin) {
    //Convert the base64 block and key to hex.
    //It's required for the encryption to work.
    qDebug() << "Encoded block: " << chunk_block;
    QString encoded_block = "";

    if (chunk_block.length() == 16) {
        encoded_block = chunk_block;
    } else {
        QByteArray chunkhex = chunk_block.toUtf8().toHex().toUpper();
        encoded_block = chunkhex;
    }

    encoded_block = hex_to_bin(encoded_block);
    encoded_block = permute(encoded_block, initial_perm, 64);
    qDebug() << "Initial permutation of block: " << bin_to_hex(encoded_block);

    //Split the text
    QString blockleft = encoded_block.sliced(0,32);
    QString blockright = encoded_block.sliced(32, 32);
    qDebug() << "Block left:" << blockleft << "Block right:" << blockright;

    //Where the actual encryption happens
    for (int i=0; i < 16; i++) {
        //Use the Expansion D-box to expand the bits from 32 to 48 bits
        QString right_expanded = permute(blockright, exp_d, 48);
        qDebug() << "Expanded right D-box:" << right_expanded;

        //XOR current round key and expanded right
        QString xor_op = xor_add(right_expanded, roundkeylist_bin[i]);

        qDebug() << "XOR result:" << xor_op;

        //Using S-box table for calculating row and column
        QString sbox_str = "";

        for (int j = 0; j < 8; j++) {
            QString chunk = xor_op.mid(j * 6,6);
            QString rowbits = QString(chunk[0]) + chunk[5];
            QString colbits = chunk.mid(1,4);

            int row = bin_to_dec(rowbits);
            int col = bin_to_dec(colbits);

            int value = sbox[j][row][col];
            //qDebug() << "Row:" << row << "Col:" << col << "Value:" << value;
            sbox_str = sbox_str + dec_to_bin(value);
        }

        //Now permute with the straight permutation table
        sbox_str = permute(sbox_str, per, 32);

        //XOR left and sbox_str
        QString result = xor_add(blockleft, sbox_str);
        blockleft = result;

        if (i != 15) {
            QString temp = blockleft;
            blockleft = blockright;
            blockright = temp;
        }

        qDebug() << "Round" << i + 1 << bin_to_hex(blockleft) << bin_to_hex(blockright) << roundkeylist[i];
    }
    //qDebug() << "\n";
    QString combine = blockleft + blockright;

    //Now for the final permutation
    QString ciphertext = permute(combine, final_perm, 64);
    QString result = bin_to_hex(ciphertext);

    return result;
}

//Decryption function with the chunk block, same or different key, and our round key lists
QString StartMenu::des_decrypt(QString &encrypted_block, QStringList &roundkeylist, QStringList &roundkeylist_bin) {

    //Convert the base64 block and key to hex.
    //It's required for the encryption to work.
    QString encoded_block = encrypted_block;
    qDebug() << "Encoded block: " << encoded_block;

    encoded_block = hex_to_bin(encoded_block);
    encoded_block = permute(encoded_block, initial_perm, 64);
    qDebug() << "Initial permutation of block: " << bin_to_hex(encoded_block);

    //Split the text
    QString blockleft = encoded_block.sliced(0,32);
    QString blockright = encoded_block.sliced(32, 32);
    qDebug() << "Block left:" << blockleft << "Block right:" << blockright;

    //Where the actual encryption happens
    for (int i=0; i < 16; i++) {
        //Use the Expansion D-box to expand the bits from 32 to 48 bits
        QString right_expanded = permute(blockright, exp_d, 48);
        qDebug() << "Expanded right D-box:" << right_expanded;

        //XOR current round key and expanded right
        QString xor_op = xor_add(right_expanded, roundkeylist_bin[i]);

        qDebug() << "XOR result:" << xor_op;

        //Using S-box table for calculating row and column
        QString sbox_str = "";

        for (int j = 0; j < 8; j++) {
            QString chunk = xor_op.mid(j * 6,6);
            QString rowbits = QString(chunk[0]) + chunk[5];
            QString colbits = chunk.mid(1,4);

            int row = bin_to_dec(rowbits);
            int col = bin_to_dec(colbits);

            int value = sbox[j][row][col];
            //qDebug() << "Row:" << row << "Col:" << col << "Value:" << value;
            sbox_str = sbox_str + dec_to_bin(value);
        }

        //Now permute with the straight permutation table
        sbox_str = permute(sbox_str, per, 32);

        //XOR left and sbox_str
        QString result = xor_add(blockleft, sbox_str);
        blockleft = result;

        if (i != 15) {
            QString temp = blockleft;
            blockleft = blockright;
            blockright = temp;
        }

        qDebug() << "Round" << i + 1 << bin_to_hex(blockleft) << bin_to_hex(blockright) << roundkeylist[i];
    }
    qDebug() << "\n";
    QString combine = blockleft + blockright;

    //Now for the final permutation
    QString ciphertext = permute(combine, final_perm, 64);
    QString result = bin_to_hex(ciphertext);
    qDebug() << "Ciphered chunk (Hex):" << bin_to_hex(ciphertext) << "(Bin):" << ciphertext << "\n";
    return result;
}

void StartMenu::TDES(QFile &ploot_out_file) {
    //keys are 8 digits and later converted to 8 hex values (16 chars)
    QString key1 = "34827168"; //key 1 encryption step 1
    QString key2 = "43712987"; //key 2 decryption step 2
    QString key3 = "58901264"; //key 3 encryption step 3
    int step = 0; //Step counter for encryption steps
    QStringList cipher_blocks;
    QString ci_chunk = ""; //Ciphered chunk
    //Store the round key for later
    QStringList roundkeylist = {};
    QStringList roundkeylist_bin = {};
    QStringList roundkeylist2 = {};
    QStringList roundkeylist2_bin = {};
    QStringList roundkeylist3 = {};
    QStringList roundkeylist3_bin = {};

    //Generate round keys for each step
    keygen(key1, roundkeylist, roundkeylist_bin);
    keygen(key2, roundkeylist2, roundkeylist2_bin);
    keygen(key3, roundkeylist3, roundkeylist3_bin);

    step++;

    if (step == 1) {
        if (ploot_out_file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&ploot_out_file);

            //Declare two pointers for string reading
            int start;
            int end;
            QString chunk;
            bool fix_chunk = false;

            while (!ploot_out_file.atEnd()) {
                start = 0;
                end = 8;

                QByteArray line = in.readLine().toUtf8();
                int str_len = line.length(); //The line of string's length

                while (start <= end) {
                    chunk.append(line[start]);
                    start++;

                    if (start == str_len) {
                        //If the chunk is less than 8 characters (8 bytes), pad it out
                        if (chunk.length() < 8) {
                            fix_chunk = true;

                            if (fix_chunk) {
                                while (chunk.length() < 8) {
                                    chunk.append("$");
                                }
                                qDebug() << "Fixed Chunk: " << chunk;
                                ci_chunk = des_encrypt(chunk, roundkeylist, roundkeylist_bin);
                                cipher_blocks.append(ci_chunk);
                                chunk.clear();
                            }
                            fix_chunk = false;
                        }

                        else if (chunk.length() == 8) {
                            //The chunk is good
                            qDebug() << "Ok Chunk: " << chunk;
                            ci_chunk = des_encrypt(chunk, roundkeylist, roundkeylist_bin);
                            cipher_blocks.append(ci_chunk);
                            chunk.clear();
                        }
                        break;
                    }
                    else if (start == end) {
                        //Print the chunk when the start pointer equals the end pointer. Then increase the end's pointer if possible.
                        qDebug() << "Good Chunk: " << chunk;
                        end += 8;
                        ci_chunk = des_encrypt(chunk, roundkeylist, roundkeylist_bin);
                        cipher_blocks.append(ci_chunk);
                        chunk.clear();
                    }
                }
            }
            ploot_out_file.close();
            qDebug() << "Step" << step << "complete! Ciphered blocks list:\n" << cipher_blocks << "\n";
            step++;
        }
    }
    if (step == 2) {
        //Reverse the round keys for the decryption
        //Pass in key 2 for the decryption
        std::reverse(roundkeylist2.begin(), roundkeylist2.end());
        std::reverse(roundkeylist2_bin.begin(), roundkeylist2_bin.end());

        for (int i = 0; i < cipher_blocks.length(); i++) {
            ci_chunk = des_decrypt(cipher_blocks[i], roundkeylist, roundkeylist_bin);
            cipher_blocks[i] = ci_chunk;
        }
        qDebug() << "Step" << step << "complete! Deciphered blocks list:\n" << cipher_blocks;
        step++;

        for (QString block : cipher_blocks) {
            qDebug() << "Decrypted block:" << hex_to_char(block);
        }
    }
    if (step == 3) {
        //Reverse the round keys for the decryption
        //Pass in key 3 for the encryption
        //qDebug() << "Checking for blocks list:\n" << cipher_blocks;
        for (int i = 0; i < cipher_blocks.length(); i++) {
            ci_chunk = des_encrypt(cipher_blocks[i], roundkeylist3, roundkeylist3_bin);
            cipher_blocks[i] = ci_chunk;
        }
        qDebug() << "Step" << step << "complete! Ciphered blocks list:\n" << cipher_blocks << "\nEncryption complete! Results are in the output file.";
        for (QString block : cipher_blocks) {
            qDebug() << "Encrypted block:" << block;
        }
        step++;
    }
}

StartMenu::StartMenu(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::StartMenu)
{
    ui->setupUi(this);
}

StartMenu::~StartMenu()
{
    delete ui;
}

void StartMenu::on_pushButton_clicked()
{
    //Open the file dialog
    QString ploot_file = QFileDialog::getOpenFileName(
        this,
        "Open Ploot",
        "",
        "Ploot (*.ploot)"
        );

    //If the ploot file isn't empty, start encrypting
    if (!ploot_file.isEmpty()) {
        QFile file(ploot_file);

        QStringList lines;

        if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&file);
            while (!in.atEnd()) {
                QString currentLine = in.readLine();

                //Convert the line to regular string for conversion
                auto converted_line = currentLine.toStdString();
                auto encoded = base64::to_base64(converted_line);

                //Convert the string back to a QString
                QString encoded_line = QString::fromStdString(encoded);
                //qDebug() << "Encoded line: " << encoded_line;

                //Append the line to the new encrypted ploot file
                lines.append(encoded_line);
            }
        }
        file.close();

        //Create a new encrypted ploot file
        QFile ploot_out(QFileInfo(file).fileName());

        if (ploot_out.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&ploot_out);

            //Separate each line
            for (const QString &line : lines) {
                out << line << "\n";
            }

            //Hide it's creation time
            QDateTime dt(QDate(2000, 1, 1), QTime(0, 0));

            ploot_out.setFileTime(dt, QFileDevice::FileModificationTime);
            ploot_out.setFileTime(dt, QFileDevice::FileBirthTime);
            ploot_out.setFileTime(dt, QFileDevice::FileAccessTime);

            ploot_out.close();
        }
        TDES(ploot_out);
    }
}


void StartMenu::on_pushButton_2_clicked()
{
    QCoreApplication::quit();
}


void StartMenu::on_actionExit_triggered()
{
    QCoreApplication::quit();
}


void StartMenu::on_actionOpen_triggered()
{
    StartMenu::on_pushButton_clicked();
}

