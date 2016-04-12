
/*
 * sophia database
 * sphia.org
 *
 * Copyright (c) Dmitry Simonenko
 * BSD License
*/

#include <sophia.h>
#include <libss.h>
#include <libsf.h>
#include <libsr.h>
#include <libsv.h>
#include <libsd.h>
#include <libst.h>

static void
multipart_cmp_eq_key(void)
{
	void *env = sp_env();
	t( env != NULL );
	t( sp_setstring(env, "sophia.path", st_r.conf->sophia_dir, 0) == 0 );
	t( sp_setint(env, "scheduler.threads", 0) == 0 );
	t( sp_setstring(env, "log.path", st_r.conf->log_dir, 0) == 0 );
	t( sp_setstring(env, "db", "test", 0) == 0 );
	t( sp_setstring(env, "db.test.path", st_r.conf->db_dir, 0) == 0 );
	t( sp_setstring(env, "db.test.scheme", "key", 0) == 0 );
	t( sp_setstring(env, "db.test.scheme.key", "u32,key(0)", 0) == 0 );
	t( sp_setstring(env, "db.test.scheme", "value", 0) == 0 );
	t( sp_setint(env, "db.test.sync", 0) == 0 );

	char *v = sp_getstring(env, "db.test.scheme.key", 0);
	t( strcmp(v, "u32,key(0)") == 0 );
	free(v);

	t( sp_open(env) == 0 );
	t( sp_destroy(env) == 0 );
}

static void
multipart_schema0(void)
{
	void *env = sp_env();
	t( env != NULL );
	t( sp_setstring(env, "sophia.path", st_r.conf->sophia_dir, 0) == 0 );
	t( sp_setint(env, "scheduler.threads", 0) == 0 );
	t( sp_setstring(env, "log.path", st_r.conf->log_dir, 0) == 0 );
	t( sp_setstring(env, "db", "test", 0) == 0 );
	t( sp_setstring(env, "db.test.path", st_r.conf->db_dir, 0) == 0 );
	t( sp_setstring(env, "db.test.scheme", "key", 0) == 0 );
	t( sp_setstring(env, "db.test.scheme", "key_b", 0) == 0 );
	t( sp_setstring(env, "db.test.scheme", "value", 0) == 0 );
	t( sp_setstring(env, "db.test.scheme.key", "string,key(0)", 0) == 0 );
	t( sp_setstring(env, "db.test.scheme.key_b", "string", 0) == 0 );
	t( sp_setint(env, "db.test.sync", 0) == 0 );

	char *v = sp_getstring(env, "db.test.scheme.key", 0);
	t( strcmp(v, "string,key(0)") == 0 );
	free(v);

	v = sp_getstring(env, "db.test.scheme.key_b", 0);
	t( strcmp(v, "string") == 0 );
	free(v);

	t( sp_setstring(env, "db.test.scheme.key_b", "u32,key(1)", 0) == 0 );

	v = sp_getstring(env, "db.test.scheme.key_b", 0);
	t( strcmp(v, "u32,key(1)") == 0 );
	free(v);

	t( sp_open(env) == 0 );

	t( sp_setstring(env, "db.test.scheme.key_b", "string", 0) == -1 );
	t( sp_destroy(env) == 0 );
}

static void
multipart_schema1(void)
{
	void *env = sp_env();
	t( env != NULL );
	t( sp_setstring(env, "sophia.path", st_r.conf->sophia_dir, 0) == 0 );
	t( sp_setint(env, "scheduler.threads", 0) == 0 );
	t( sp_setstring(env, "log.path", st_r.conf->log_dir, 0) == 0 );
	t( sp_setstring(env, "db", "test", 0) == 0 );
	t( sp_setstring(env, "db.test.path", st_r.conf->db_dir, 0) == 0 );
	t( sp_setstring(env, "db.test.scheme", "key", 0) == 0 );
	t( sp_setstring(env, "db.test.scheme", "key_b", 0) == 0 );
	t( sp_setstring(env, "db.test.scheme.key", "u32,key(0)", 0) == 0 );
	t( sp_setstring(env, "db.test.scheme.key_b", "string,key(0)", 0) == 0 );
	t( sp_setint(env, "db.test.sync", 0) == 0 );
	t( sp_open(env) == -1 );

	t( sp_destroy(env) == 0 );
}

static void
multipart_schema2(void)
{
	void *env = sp_env();
	t( env != NULL );
	t( sp_setstring(env, "sophia.path", st_r.conf->sophia_dir, 0) == 0 );
	t( sp_setint(env, "scheduler.threads", 0) == 0 );
	t( sp_setstring(env, "log.path", st_r.conf->log_dir, 0) == 0 );
	t( sp_setstring(env, "db", "test", 0) == 0 );
	t( sp_setstring(env, "db.test.path", st_r.conf->db_dir, 0) == 0 );
	t( sp_setstring(env, "db.test.scheme", "key", 0) == 0 );
	t( sp_setstring(env, "db.test.scheme", "key_b", 0) == 0 );
	t( sp_setstring(env, "db.test.scheme.key", "u32,key(0)", 0) == 0 );
	t( sp_setstring(env, "db.test.scheme.key_b", "string,key(2)", 0) == 0 );
	t( sp_setint(env, "db.test.sync", 0) == 0 );
	t( sp_open(env) == -1 );
	t( sp_destroy(env) == 0 );
}

static void
multipart_schema3(void)
{
	void *env = sp_env();
	t( env != NULL );
	t( sp_setstring(env, "sophia.path", st_r.conf->sophia_dir, 0) == 0 );
	t( sp_setint(env, "scheduler.threads", 0) == 0 );
	t( sp_setstring(env, "log.path", st_r.conf->log_dir, 0) == 0 );
	t( sp_setstring(env, "db", "test", 0) == 0 );
	t( sp_setstring(env, "db.test.path", st_r.conf->db_dir, 0) == 0 );
	t( sp_setstring(env, "db.test.scheme", "key", 0) == 0 );
	t( sp_setstring(env, "db.test.scheme", "key_b", 0) == 0 );
	t( sp_setstring(env, "db.test.scheme.key", "u32,key(0)", 0) == 0 );
	t( sp_setstring(env, "db.test.scheme.key_b", "string,key()", 0) == 0 );
	t( sp_setint(env, "db.test.sync", 0) == 0 );
	t( sp_open(env) == -1 );
	t( sp_destroy(env) == 0 );
}

static void
multipart_schema4(void)
{
	void *env = sp_env();
	t( env != NULL );
	t( sp_setstring(env, "sophia.path", st_r.conf->sophia_dir, 0) == 0 );
	t( sp_setint(env, "scheduler.threads", 0) == 0 );
	t( sp_setstring(env, "log.path", st_r.conf->log_dir, 0) == 0 );
	t( sp_setstring(env, "db", "test", 0) == 0 );
	t( sp_setstring(env, "db.test.path", st_r.conf->db_dir, 0) == 0 );
	t( sp_setstring(env, "db.test.scheme", "key", 0) == 0 );
	t( sp_setstring(env, "db.test.scheme", "key_b", 0) == 0 );
	t( sp_setstring(env, "db.test.scheme.key", "u32,key(0)", 0) == 0 );
	t( sp_setstring(env, "db.test.scheme.key_b", "string,key(abc)", 0) == 0 );
	t( sp_setint(env, "db.test.sync", 0) == 0 );
	t( sp_open(env) == -1 );
	t( sp_destroy(env) == 0 );
}

static void
multipart_set_get0(void)
{
	void *env = sp_env();
	t( env != NULL );
	t( sp_setstring(env, "sophia.path", st_r.conf->sophia_dir, 0) == 0 );
	t( sp_setint(env, "scheduler.threads", 0) == 0 );
	t( sp_setstring(env, "log.path", st_r.conf->log_dir, 0) == 0 );
	t( sp_setstring(env, "db", "test", 0) == 0 );
	t( sp_setstring(env, "db.test.path", st_r.conf->db_dir, 0) == 0 );
	t( sp_setstring(env, "db.test.scheme", "key", 0) == 0 );
	t( sp_setstring(env, "db.test.scheme.key", "string,key(0)", 0) == 0 );
	t( sp_setstring(env, "db.test.scheme", "key_b", 0) == 0 );
	t( sp_setstring(env, "db.test.scheme.key_b", "u32,key(1)", 0) == 0 );
	t( sp_setstring(env, "db.test.scheme", "value", 0) == 0 );
	t( sp_setint(env, "db.test.sync", 0) == 0 );
	t( sp_open(env) == 0 );

	void *db = sp_getobject(env, "db.test");
	t( db != NULL );

	char key_a[] = "hello";
	uint32_t key_b = 7;

	void *o = sp_document(db);
	sp_setstring(o, "key", key_a, sizeof(key_a));
	sp_setstring(o, "key_b", &key_b, sizeof(key_b));
	t( sp_set(db, o) == 0);

	o = sp_document(db);
	sp_setstring(o, "key", key_a, sizeof(key_a));
	sp_setstring(o, "key_b", &key_b, sizeof(key_b));
	o = sp_get(db, o);
	t( o != NULL );
	sp_destroy(o);

	t( sp_destroy(env) == 0 );
}

static void
multipart_set_get1(void)
{
	void *env = sp_env();
	t( env != NULL );
	t( sp_setstring(env, "sophia.path", st_r.conf->sophia_dir, 0) == 0 );
	t( sp_setint(env, "scheduler.threads", 0) == 0 );
	t( sp_setstring(env, "log.path", st_r.conf->log_dir, 0) == 0 );
	t( sp_setstring(env, "db", "test", 0) == 0 );
	t( sp_setstring(env, "db.test.path", st_r.conf->db_dir, 0) == 0 );
	t( sp_setstring(env, "db.test.scheme", "key", 0) == 0 );
	t( sp_setstring(env, "db.test.scheme.key", "string,key(0)", 0) == 0 );
	t( sp_setstring(env, "db.test.scheme", "key_b", 0) == 0 );
	t( sp_setstring(env, "db.test.scheme.key_b", "u32,key(1)", 0) == 0 );
	t( sp_setstring(env, "db.test.scheme", "value", 0) == 0 );
	t( sp_setint(env, "db.test.sync", 0) == 0 );
	t( sp_open(env) == 0 );

	void *db = sp_getobject(env, "db.test");
	t( db != NULL );

	char key_a[] = "hello";
	uint32_t i = 0;
	while (i < 546) {
		void *o = sp_document(db);
		sp_setstring(o, "key", key_a, sizeof(key_a));
		sp_setstring(o, "key_b", &i, sizeof(i));
		sp_setstring(o, "value", &i, sizeof(i));
		t( sp_set(db, o) == 0);
		i++;
	}

	i = 0;
	while (i < 546) {
		void *o = sp_document(db);
		sp_setstring(o, "key", key_a, sizeof(key_a));
		sp_setstring(o, "key_b", &i, sizeof(i));
		o = sp_get(db, o);
		t( o != NULL );
		int asize;
		t( strcmp(key_a, sp_getstring(o, "key", &asize)) == 0 );
		int bsize;
		t( *(uint32_t*)sp_getstring(o, "key_b", &bsize) == i );
		int vsize;
		t( *(uint32_t*)sp_getstring(o, "value", &vsize) == i );
		t( asize == sizeof(key_a) );
		t( bsize == sizeof(i) );
		t( vsize == sizeof(i) );
		sp_destroy(o);
		i++;
	}

	t( sp_destroy(env) == 0 );
}

static void
multipart_set_get2(void)
{
	void *env = sp_env();
	t( env != NULL );
	t( sp_setstring(env, "sophia.path", st_r.conf->sophia_dir, 0) == 0 );
	t( sp_setint(env, "scheduler.threads", 0) == 0 );
	t( sp_setstring(env, "log.path", st_r.conf->log_dir, 0) == 0 );
	t( sp_setstring(env, "db", "test", 0) == 0 );
	t( sp_setstring(env, "db.test.path", st_r.conf->db_dir, 0) == 0 );
	t( sp_setstring(env, "db.test.scheme", "key", 0) == 0 );
	t( sp_setstring(env, "db.test.scheme.key", "string,key(1)", 0) == 0 );
	t( sp_setstring(env, "db.test.scheme", "key_b", 0) == 0 );
	t( sp_setstring(env, "db.test.scheme.key_b", "u32,key(0)", 0) == 0 );
	t( sp_setstring(env, "db.test.scheme", "value", 0) == 0 );
	t( sp_setint(env, "db.test.sync", 0) == 0 );
	t( sp_open(env) == 0 );

	void *db = sp_getobject(env, "db.test");
	t( db != NULL );

	char key_a[] = "hello";
	uint32_t i = 0;
	while (i < 546) {
		void *o = sp_document(db);
		sp_setstring(o, "key", key_a, sizeof(key_a));
		sp_setstring(o, "key_b", &i, sizeof(i));
		sp_setstring(o, "value", &i, sizeof(i));
		t( sp_set(db, o) == 0);
		i++;
	}

	i = 0;
	while (i < 546) {
		void *o = sp_document(db);
		sp_setstring(o, "key", key_a, sizeof(key_a));
		sp_setstring(o, "key_b", &i, sizeof(i));
		o = sp_get(db, o);
		t( o != NULL );
		int asize;
		t( strcmp(key_a, sp_getstring(o, "key", &asize)) == 0 );
		int bsize;
		t( *(uint32_t*)sp_getstring(o, "key_b", &bsize) == i );
		int vsize;
		t( *(uint32_t*)sp_getstring(o, "value", &vsize) == i );
		t( asize == sizeof(key_a) );
		t( bsize == sizeof(i) );
		t( vsize == sizeof(i) );
		sp_destroy(o);
		i++;
	}

	t( sp_destroy(env) == 0 );
}

static void
multipart_cursor0(void)
{
	void *env = sp_env();
	t( env != NULL );
	t( sp_setstring(env, "sophia.path", st_r.conf->sophia_dir, 0) == 0 );
	t( sp_setint(env, "scheduler.threads", 0) == 0 );
	t( sp_setstring(env, "log.path", st_r.conf->log_dir, 0) == 0 );
	t( sp_setstring(env, "db", "test", 0) == 0 );
	t( sp_setstring(env, "db.test.path", st_r.conf->db_dir, 0) == 0 );
	t( sp_setstring(env, "db.test.scheme", "key", 0) == 0 );
	t( sp_setstring(env, "db.test.scheme.key", "string,key(0)", 0) == 0 );
	t( sp_setstring(env, "db.test.scheme", "key_b", 0) == 0 );
	t( sp_setstring(env, "db.test.scheme.key_b", "u32,key(1)", 0) == 0 );
	t( sp_setstring(env, "db.test.scheme", "value", 0) == 0 );
	t( sp_setint(env, "db.test.sync", 0) == 0 );
	t( sp_open(env) == 0 );

	void *db = sp_getobject(env, "db.test");
	t( db != NULL );

	char key_a[] = "hello";
	uint32_t i = 0;
	while (i < 546) {
		void *o = sp_document(db);
		sp_setstring(o, "key", key_a, sizeof(key_a));
		sp_setstring(o, "key_b", &i, sizeof(i));
		sp_setstring(o, "value", &i, sizeof(i));
		t( sp_set(db, o) == 0);
		i++;
	}

	i = 0;
	void *cur = sp_cursor(env);
	t( cur != NULL );
	void *o = sp_document(db);
	while ((o = sp_get(cur, o))) {
		int asize;
		t( strcmp(key_a, sp_getstring(o, "key", &asize)) == 0 );
		int bsize;
		t( *(uint32_t*)sp_getstring(o, "key_b", &bsize) == i );
		int vsize;
		t( *(uint32_t*)sp_getstring(o, "value", &vsize) == i );
		t( asize == sizeof(key_a) );
		t( bsize == sizeof(i) );
		t( vsize == sizeof(i) );
		i++;
	}
	sp_destroy(cur);

	t( sp_destroy(env) == 0 );
}

static void
multipart_cursor1(void)
{
	void *env = sp_env();
	t( env != NULL );
	t( sp_setstring(env, "sophia.path", st_r.conf->sophia_dir, 0) == 0 );
	t( sp_setint(env, "scheduler.threads", 0) == 0 );
	t( sp_setstring(env, "log.path", st_r.conf->log_dir, 0) == 0 );
	t( sp_setstring(env, "db", "test", 0) == 0 );
	t( sp_setstring(env, "db.test.path", st_r.conf->db_dir, 0) == 0 );
	t( sp_setstring(env, "db.test.scheme", "key", 0) == 0 );
	t( sp_setstring(env, "db.test.scheme.key", "string,key(0)", 0) == 0 );
	t( sp_setstring(env, "db.test.scheme", "key_b", 0) == 0 );
	t( sp_setstring(env, "db.test.scheme.key_b", "u32,key(1)", 0) == 0 );
	t( sp_setstring(env, "db.test.scheme", "value", 0) == 0 );
	t( sp_setint(env, "db.test.sync", 0) == 0 );
	t( sp_open(env) == 0 );

	void *db = sp_getobject(env, "db.test");
	t( db != NULL );

	char key_a[] = "hello";
	uint32_t i = 0;
	while (i < 546) {
		void *o = sp_document(db);
		sp_setstring(o, "key", key_a, sizeof(key_a));
		sp_setstring(o, "key_b", &i, sizeof(i));
		sp_setstring(o, "value", &i, sizeof(i));
		t( sp_set(db, o) == 0);
		i++;
	}

	i = 322;
	void *cur = sp_cursor(env);
	t( cur != NULL );
	void *o = sp_document(db);
	sp_setstring(o, "key", key_a, sizeof(key_a));
	sp_setstring(o, "key_b", &i, sizeof(i));
	sp_setstring(o, "value", &i, sizeof(i));
	while ((o = sp_get(cur, o))) {
		int asize;
		t( strcmp(key_a, sp_getstring(o, "key", &asize)) == 0 );
		int bsize;
		t( *(uint32_t*)sp_getstring(o, "key_b", &bsize) == i );
		int vsize;
		t( *(uint32_t*)sp_getstring(o, "value", &vsize) == i );
		t( asize == sizeof(key_a) );
		t( bsize == sizeof(i) );
		t( vsize == sizeof(i) );
		i++;
	}
	sp_destroy(cur);
	t( i == 546 );

	t( sp_destroy(env) == 0 );
}

static void
multipart_set_get_incomplete0(void)
{
	void *env = sp_env();
	t( env != NULL );
	t( sp_setstring(env, "sophia.path", st_r.conf->sophia_dir, 0) == 0 );
	t( sp_setint(env, "scheduler.threads", 0) == 0 );
	t( sp_setstring(env, "log.path", st_r.conf->log_dir, 0) == 0 );
	t( sp_setstring(env, "db", "test", 0) == 0 );
	t( sp_setstring(env, "db.test.path", st_r.conf->db_dir, 0) == 0 );
	t( sp_setstring(env, "db.test.scheme", "key", 0) == 0 );
	t( sp_setstring(env, "db.test.scheme.key", "string,key(0)", 0) == 0 );
	t( sp_setstring(env, "db.test.scheme", "key_b", 0) == 0 );
	t( sp_setstring(env, "db.test.scheme.key_b", "u32,key(1)", 0) == 0 );
	t( sp_setstring(env, "db.test.scheme", "value", 0) == 0 );
	t( sp_setint(env, "db.test.sync", 0) == 0 );
	t( sp_open(env) == 0 );

	void *db = sp_getobject(env, "db.test");
	t( db != NULL );

	char key_a[] = "hello";
	uint32_t key_b = 7;

	void *o = sp_document(db);
	sp_setstring(o, "key", key_a, sizeof(key_a));
	t( sp_set(db, o) == -1 );

	o = sp_document(db);
	sp_setstring(o, "key", key_a, sizeof(key_a));
	sp_setstring(o, "key_b", &key_b, sizeof(key_b));
	t( sp_set(db, o) == 0);

	o = sp_document(db);
	sp_setstring(o, "key", key_a, sizeof(key_a));
	o = sp_get(db, o);
	t( o == NULL );

	o = sp_document(db);
	sp_setstring(o, "key", key_a, sizeof(key_a));
	sp_setstring(o, "order", ">=", 0);
	o = sp_get(db, o);
	t( o != NULL );
	sp_destroy(o);

	t( sp_destroy(env) == 0 );
}

static void
multipart_set_get_incomplete1(void)
{
	void *env = sp_env();
	t( env != NULL );
	t( sp_setstring(env, "sophia.path", st_r.conf->sophia_dir, 0) == 0 );
	t( sp_setint(env, "scheduler.threads", 0) == 0 );
	t( sp_setstring(env, "log.path", st_r.conf->log_dir, 0) == 0 );
	t( sp_setstring(env, "db", "test", 0) == 0 );
	t( sp_setstring(env, "db.test.path", st_r.conf->db_dir, 0) == 0 );
	t( sp_setstring(env, "db.test.scheme", "key", 0) == 0 );
	t( sp_setstring(env, "db.test.scheme.key", "string,key(0)", 0) == 0 );
	t( sp_setstring(env, "db.test.scheme", "key_b", 0) == 0 );
	t( sp_setstring(env, "db.test.scheme.key_b", "u32,key(1)", 0) == 0 );
	t( sp_setstring(env, "db.test.scheme", "value", 0) == 0 );
	t( sp_setint(env, "db.test.sync", 0) == 0 );
	t( sp_open(env) == 0 );

	void *db = sp_getobject(env, "db.test");
	t( db != NULL );

	char key_a[] = "hello";
	uint32_t key_b = 7;

	void *o = sp_document(db);
	sp_setstring(o, "key", key_a, sizeof(key_a));
	sp_setstring(o, "key_b", &key_b, sizeof(key_b));
	t( sp_set(db, o) == 0);

	key_b = 8;

	o = sp_document(db);
	sp_setstring(o, "key", key_a, sizeof(key_a));
	sp_setstring(o, "key_b", &key_b, sizeof(key_b));
	t( sp_set(db, o) == 0);

	o = sp_document(db);
	sp_setstring(o, "key", key_a, sizeof(key_a));
	sp_setstring(o, "order", ">=", 0);
	o = sp_get(db, o);
	t( o != NULL );
	t( *(uint32_t*)sp_getstring(o, "key_b", NULL) == 7 );
	sp_destroy(o);

	o = sp_document(db);
	sp_setstring(o, "key", key_a, sizeof(key_a));
	sp_setstring(o, "order", ">", 0);
	o = sp_get(db, o);
	t( o != NULL );
	t( *(uint32_t*)sp_getstring(o, "key_b", NULL) == 7 );
	sp_destroy(o);

	o = sp_document(db);
	sp_setstring(o, "key", key_a, sizeof(key_a));
	sp_setstring(o, "order", "<=", 0);
	o = sp_get(db, o);
	t( o != NULL );
	t( *(uint32_t*)sp_getstring(o, "key_b", NULL) == 8 );
	sp_destroy(o);

	o = sp_document(db);
	sp_setstring(o, "key", key_a, sizeof(key_a));
	sp_setstring(o, "order", "<", 0);
	o = sp_get(db, o);
	t( o != NULL );
	t( *(uint32_t*)sp_getstring(o, "key_b", NULL) == 8 );
	sp_destroy(o);

	t( sp_destroy(env) == 0 );
}

static void
multipart_set_get_incomplete2(void)
{
	void *env = sp_env();
	t( env != NULL );
	t( sp_setstring(env, "sophia.path", st_r.conf->sophia_dir, 0) == 0 );
	t( sp_setint(env, "scheduler.threads", 0) == 0 );
	t( sp_setstring(env, "log.path", st_r.conf->log_dir, 0) == 0 );
	t( sp_setstring(env, "db", "test", 0) == 0 );
	t( sp_setstring(env, "db.test.path", st_r.conf->db_dir, 0) == 0 );
	t( sp_setstring(env, "db.test.scheme", "key", 0) == 0 );
	t( sp_setstring(env, "db.test.scheme.key", "string,key(0)", 0) == 0 );
	t( sp_setstring(env, "db.test.scheme", "key_b", 0) == 0 );
	t( sp_setstring(env, "db.test.scheme.key_b", "string,key(1)", 0) == 0 );
	t( sp_setstring(env, "db.test.scheme", "value", 0) == 0 );
	t( sp_setint(env, "db.test.sync", 0) == 0 );
	t( sp_open(env) == 0 );

	void *db = sp_getobject(env, "db.test");
	t( db != NULL );

	char key_a[] = "hello";
	char key_b[] = "g";
	char key_c[] = "zzz";

	void *o = sp_document(db);
	sp_setstring(o, "key", key_a, sizeof(key_a));
	sp_setstring(o, "key_b", &key_b, sizeof(key_b));
	t( sp_set(db, o) == 0);

	o = sp_document(db);
	sp_setstring(o, "key", key_a, sizeof(key_a));
	sp_setstring(o, "key_b", &key_c, sizeof(key_c));
	t( sp_set(db, o) == 0);

	o = sp_document(db);
	sp_setstring(o, "key", key_a, sizeof(key_a));
	sp_setstring(o, "order", ">=", 0);
	o = sp_get(db, o);
	t( o != NULL );
	t( memcmp( sp_getstring(o, "key_b", NULL), key_b, 1) == 0 );
	sp_destroy(o);

	o = sp_document(db);
	sp_setstring(o, "key", key_a, sizeof(key_a));
	sp_setstring(o, "order", "<=", 0);
	o = sp_get(db, o);
	t( o != NULL );
	t( memcmp( sp_getstring(o, "key_b", NULL), key_c, 3) == 0 );
	sp_destroy(o);

	t( sp_destroy(env) == 0 );
}

stgroup *multipart_group(void)
{
	stgroup *group = st_group("multipart");
	st_groupadd(group, st_test("cmp_eq_key", multipart_cmp_eq_key));
	st_groupadd(group, st_test("schema0", multipart_schema0));
	st_groupadd(group, st_test("schema1", multipart_schema1));
	st_groupadd(group, st_test("schema2", multipart_schema2));
	st_groupadd(group, st_test("schema3", multipart_schema3));
	st_groupadd(group, st_test("schema4", multipart_schema4));
	st_groupadd(group, st_test("set_get0", multipart_set_get0));
	st_groupadd(group, st_test("set_get1", multipart_set_get1));
	st_groupadd(group, st_test("set_get2", multipart_set_get2));
	st_groupadd(group, st_test("cursor0", multipart_cursor0));
	st_groupadd(group, st_test("cursor1", multipart_cursor1));
	st_groupadd(group, st_test("set_get_incomplete0", multipart_set_get_incomplete0));
	st_groupadd(group, st_test("set_get_incomplete1", multipart_set_get_incomplete1));
	st_groupadd(group, st_test("set_get_incomplete2", multipart_set_get_incomplete2));
	return group;
}
