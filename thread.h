/*-
 * Copyright (c) 2004,2005,2006 LabSEC.
 * All rights reserved.
 *
 * This code is derived from software contributed to LabSEC
 * by Tulio Salvaro and Martin Augusto Gagliotti Vigil.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *        This product includes software developed by LabSEC
 *          and its contributors.
 * 4. Neither the name of LabSEC nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY LABSEC AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef HEADER_THREAD_H
#define HEADER_THREAD_H


#include <openssl/crypto.h>
#include <pthread.h>

int THREAD_cleanup(void);
int THREAD_setup(void);

#define MUTEX_TYPE		pthread_mutex_t
#define MUTEX_SETUP(x)		pthread_mutex_init(&(x), NULL)
#define MUTEX_CLEANUP(x) 	pthread_mutex_destroy(&(x))
#define MUTEX_LOCK(x)		pthread_mutex_lock(&(x))
#define MUTEX_UNLOCK(x)		pthread_mutex_unlock(&(x))
#define MUTEX_TRYLOCK(x)		pthread_mutex_trylock(&(x))
#define THREAD_ID		pthread_self()
/**
 * redefine o tipo de uma thread
 */
#define THREAD_TYPE	pthread_t
/**
 * redefine a chamada da função que cria uma nova thread
 */
#define THREAD_CREATE(tid, entry, arg) pthread_create(&(tid), NULL, (void *)(entry), ((void *)arg))

MUTEX_TYPE mutex_write_group_database;
MUTEX_TYPE mutex_read_group_database;
int reading_group_database;

MUTEX_TYPE writing_flash_memory;
int users_writing_flash_memory;

MUTEX_TYPE mutex_smartcard_reader;

MUTEX_TYPE mutex_certificate_serial;

MUTEX_TYPE mutex_configuring_hsm;

MUTEX_TYPE mutex_write_log_database;

int THREAD_setup(void);
int THREAD_cleanup(void);

#endif /* HEADER_THREAD_H */
