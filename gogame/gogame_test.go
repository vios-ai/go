// (C) 2017-2018 All Rights Reserved Laurent Demailly.

package gogame // import "vios.ai/vios/gogame"

import (
	"fmt"
	"testing"
)

func TestGoBoard1(t *testing.T) {
	src := NewGoBoard(19)
	fmt.Printf("board %d %+v", len(src.board), src)
}

func BenchmarkNoop(b *testing.B) {
	for n := 0; n < b.N; n++ {
	}
}

func BenchmarkCopy19(b *testing.B) {
	src := NewGoBoard(19)
	dst := GoBoard{}
	for n := 0; n < b.N; n++ {
		dst.Copy1(src)
	}
}

func BenchmarkCopy13(b *testing.B) {
	src := NewGoBoard(13)
	dst := GoBoard{}
	for n := 0; n < b.N; n++ {
		dst.Copy1(src)
	}
}

func BenchmarkCopy9(b *testing.B) {
	src := NewGoBoard(9)
	dst := GoBoard{}
	for n := 0; n < b.N; n++ {
		dst.Copy1(src)
	}
}

func BenchmarkCopyAlternate(b *testing.B) {
	src1 := NewGoBoard(19)
	src2 := NewGoBoard(13)
	dst := GoBoard{}
	for n := 0; n < b.N; n++ {
		dst.Copy1(src1)
		dst.Copy1(src2)
	}
}
