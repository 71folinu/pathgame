		if (APPSTATE == PHYSICS_TEST) {
			if (IsKeyPressed(KEY_ESCAPE)) APPSTATE = TRANSITION;
			if (IsMouseButtonDown(0)) {
				physics_test_airDrag = 0.90;
				physics_test_ballXV += 0.05*(GetMouseX() - physics_test_ballX);
				physics_test_ballYV += 0.05*(GetMouseY() - physics_test_ballY);
			};
			if (IsMouseButtonReleased(0)) physics_test_airDrag = physics_test_def_airDrag;
			physics_test_ballYV += 1.5;
			physics_test_ballY += physics_test_ballYV;
			physics_test_ballX += physics_test_ballXV;
			if (physics_test_ballY+physics_test_ballRadius > height) {
				physics_test_ballY = height - physics_test_ballRadius;
				physics_test_ballYV *= -0.9;
			};
			if (physics_test_ballX+physics_test_ballRadius > width) {
				physics_test_ballX = width - physics_test_ballRadius;
				physics_test_ballXV *= -0.9;
			};
			if (physics_test_ballX-physics_test_ballRadius < 0) {
				physics_test_ballX = 0 + physics_test_ballRadius;
				physics_test_ballXV *= -0.9;
			};
			if (physics_test_ballY-physics_test_ballRadius < 0) {
				physics_test_ballY = 0 + physics_test_ballRadius;
				physics_test_ballYV *= -0.9;
			};
			physics_test_ballXV *= physics_test_airDrag;
			physics_test_ballYV *= physics_test_airDrag;
			ClearBackground(GRAY);
			DrawCircle(physics_test_ballX,physics_test_ballY,physics_test_ballRadius,WHITE);
		};
