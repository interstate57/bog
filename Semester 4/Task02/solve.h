#include "io_status.h"
#include "request.h"

io_status solve1(char* a, char* b, char* s, char* t, int m, int* r){
    FILE* in;
    FILE* out;
    if (!(in = fopen(a, "r"))){
        return io_status::open_error_a;
    }
    if (!(out = fopen(b, "w"))){
        fclose(in);
        return io_status::open_error_b;
    }
    request_b_tree tree(m);
    tree.parse_t(t);
    io_status ret = tree.parse_s(s, t);
    if (ret != io_status::success){
        fclose(in);
        fclose(out);
        return ret;
    }
    char buf[LEN];
    int cnt = 0;
    while(fgets(buf, LEN, in) != 0) {
		for(int i = 0; buf[i]; ++i) {
			if(buf[i] == '\n') {
				buf[i] = 0; 
				break;
			}
		}
		if (tree.context_fit(buf) == 1) {
			fprintf(out, "%s\n", buf);
			cnt += 1;
		}
	}
    *r = cnt;
    fclose(out);
    if (!feof(in)){
        fclose(in);
        return io_status::eof;
    }
    fclose(in);
    return io_status::success;
}

io_status solve2(char* a, char* b, char* s, char* t, int* r){
    FILE* in;
    FILE* out;
    if (!(in = fopen(a, "r"))){
        return io_status::open_error_a;
    }
    if (!(out = fopen(b, "w"))){
        fclose(in);
        return io_status::open_error_b;
    }
    request_rb_tree tree;
    tree.parse_t(t);
    io_status ret = tree.parse_s(s, t);
    if (ret != io_status::success){
        fclose(in);
        fclose(out);
        return ret;
    }
    char buf[LEN];
    int cnt = 0;
    while(fgets(buf, LEN, in) != 0) {
		for(int i = 0; buf[i]; ++i) {
			if(buf[i] == '\n') {
				buf[i] = 0; 
				break;
			}
		}
		if (tree.context_fit(buf) == 1) {
			fprintf(out, "%s\n", buf);
			cnt += 1;
		}
	}
    *r = cnt;
    fclose(out);
    if (!feof(in)){
        fclose(in);
        return io_status::eof;
    }
    fclose(in);
    return io_status::success;
}

io_status solve4(char* a, char* b, char* s, char* t, char* x, int* r){
    FILE* in;
    FILE* out;
    if (!(in = fopen(a, "r"))){
        return io_status::open_error_a;
    }
    if (!(out = fopen(b, "w"))){
        fclose(in);
        return io_status::open_error_b;
    }
    request_4 request;
    request.parse_t(t);
    io_status ret = request.parse_s_and_x(s, x, t);
    if (ret != io_status::success){
        fclose(in);
        fclose(out);
        return ret;
    }
    char buf[LEN];
    int cnt = 0;
    while(fgets(buf, LEN, in) != 0) {
		for(int i = 0; buf[i]; ++i) {
			if(buf[i] == '\n') {
				buf[i] = 0; 
				break;
			}
		}
		if (request.context_fit(buf) == 1) {
			fprintf(out, "%s\n", buf);
			cnt += 1;
		}
	}
    *r = cnt;
    fclose(out);
    if (!feof(in)){
        fclose(in);
        return io_status::eof;
    }
    fclose(in);
    return io_status::success;
}

io_status solve5(char* a, char* b, char* s, char* t, char* x, int* r){
    FILE* in;
    FILE* out;
    if (!(in = fopen(a, "r"))){
        return io_status::open_error_a;
    }
    if (!(out = fopen(b, "w"))){
        fclose(in);
        return io_status::open_error_b;
    }
    request_5 request;
    request.parse_t(t);
    io_status ret = request.parse_s_and_x(s, x, t);
    if (ret != io_status::success){
        fclose(in);
        fclose(out);
        return ret;
    }
    char buf[LEN];
    int cnt = 0;
    while(fgets(buf, LEN, in) != 0) {
		for(int i = 0; buf[i]; ++i) {
			if(buf[i] == '\n') {
				buf[i] = 0; 
				break;
			}
		}
		if (request.context_fit(buf) == 1) {
			fprintf(out, "%s\n", buf);
			cnt += 1;
		}
	}
    *r = cnt;
    fclose(out);
    if (!feof(in)){
        fclose(in);
        return io_status::eof;
    }
    fclose(in);
    return io_status::success;
}

io_status solve6(char* a, char* b, char* s, char* t, int* r){
    FILE* in;
    FILE* out;
    if (!(in = fopen(a, "r"))){
        return io_status::open_error_a;
    }
    if (!(out = fopen(b, "w"))){
        fclose(in);
        return io_status::open_error_b;
    }
    request_6 request;
    request.parse_t(t);
    io_status ret = request.parse_s(s);
    if (ret != io_status::success){
        fclose(in);
        fclose(out);
        return ret;
    }
    char buf[LEN];
    int cnt = 0;
    while(fgets(buf, LEN, in) != 0) {
		for(int i = 0; buf[i]; ++i) {
			if(buf[i] == '\n') {
				buf[i] = 0; 
				break;
			}
		}
		if (request.context_fit(buf) == 1) {
			fprintf(out, "%s\n", buf);
			cnt += 1;
		}
	}
    *r = cnt;
    fclose(out);
    if (!feof(in)){
        fclose(in);
        return io_status::eof;
    }
    fclose(in);
    return io_status::success;
}