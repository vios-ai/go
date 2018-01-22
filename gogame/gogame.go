// (C) 2017-2018 All Rights Reserved Laurent Demailly.

package gogame // import "vios.ai/vios/gogame"

// GoBoard is the go game/board structure.
// optimized for copying. Loosely based on
// https://github.com/vios-ai/go-ui/blob/master/goban.js
type GoBoard struct {
	n     int
	board []int16
}

// NewGoBoard creates a new board at requested size.
func NewGoBoard(sz int) GoBoard {
	return GoBoard{
		n:     sz,
		board: make([]int16, sz*sz),
	}
}

// Copy1 clones the board.
func (g *GoBoard) Copy1(src GoBoard) {
	g.n = src.n
	g.board = make([]int16, len(src.board))
	copy(g.board, src.board)
}
