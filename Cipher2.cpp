///*
// * Cipher2.cpp
// *
// *  Created on: Nov 12, 2013
// *      Author: rick
// */
//
//#include "Cipher2.h"
//
//Cipher2::Cipher2() {
//	// TODO Auto-generated constructor stub
//
//}
//
//Cipher2::~Cipher2() {
//	// TODO Auto-generated destructor stub
//}
//
//void Cipher2::openFile(char *filePath, char **buffer, int *size){
//
//		FILE *file;
//		long lSize;
//
//		file = fopen(filePath, "rb");
//
//		fseek(file, 0, SEEK_END);
//		lSize = ftell(file);
//		rewind(file);
//		// allocate memory to contain the whole file:
//		*buffer = (char*) (malloc(sizeof(char) * lSize));
//		if (*buffer == NULL) {
//			fputs("Memory error", stderr);
//			exit(2);
//		}
//		// copy the file into the share_buffer:
//		*size = fread(*buffer, 1, lSize, file);
//
//		fclose(file);
//	}
//
//Zr Cipher2::openShare(char *filePath, const Pairing& e){
//
//		char *buffer;
//		int size;
//
//		openFile(filePath, &buffer, &size);
//
//		char *tok;
//
//		tok = strtok(buffer, ": \n");
//		//if(tok != NULL)
//		//	tok = strtok(NULL, ":");
//
//		return Zr (e, (unsigned char *)tok, (size_t)size, 10);
//
//	}
//
//unsigned char *  Cipher2::generate_private_key(char *id, int *length){
//
//	SystemParam sysparam("pairing.param", "system.param");
//
//	const Pairing& e = sysparam.get_Pairing();
//
//	vector<G1> sharesG1;
//	vector<Zr> indices;
//
//	G1 g1_publicKey;
//
//	G1 msgHashG1;
//
//	//hash_msg(msgHashG1, id, e);
//
//	unsigned char *id_hash;
//	id_hash = (unsigned char *) malloc(SHA_DIGEST_LENGTH);
//
//	SHA1((unsigned char *) id, strlen(id), id_hash);
//
//	msgHashG1 = G1(e, (void*) id_hash, SHA_DIGEST_LENGTH);
//
//	Zr share_zr;
//	G1 share_g1;
//	share_zr = this->openShare("priv1", e);
//	share_g1 = msgHashG1 ^ share_zr;
//
//	element_s *e_share_g1;
//
//	e_share_g1 = (element_s *) share_g1.getElement();
//
//	int share_length = element_length_in_bytes(e_share_g1);
//
//	*length = share_length;
//
//	unsigned char *u_share_g1;
//
//	u_share_g1 = (unsigned char *) calloc(share_length, sizeof(unsigned char));
//
//	element_to_bytes(u_share_g1, e_share_g1);
//
//	/**
//	 * Teste
//	 */
//	//		element_t teste;
//	//
//	//		element_init_G1(teste, (pairing_s *) e.getPairing());
//	//
//	//		element_from_bytes(teste, u_share_g1);
//	//
//	//		FILE *f_priv;
//	//		f_priv = fopen("shares/priv1", "w");
//	//
//	//		        //priv.dump(f_priv, "priv1", 10);
//	//		//element_out_str(f_priv, 10, e_share_g1);
//	//		element_out_str(f_priv, 10, teste);
//	//
//	//		fclose(f_priv);
//	return u_share_g1;
//}
//
