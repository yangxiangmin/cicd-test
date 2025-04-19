pipeline {
    agent any  // 可以在任意 Jenkins Agent 上运行
    environment {
        // 定义环境变量
        BUILD_DIR = "build"
        TEST_RESULTS = "test-results.xml"
        ARTIFACT_NAME = "cicd_test_project-${env.BUILD_NUMBER}.tar.gz"
    }

    stages {
        // 阶段 1：拉取代码
        stage('Checkout') {
            steps {
                git branch: 'main', url: 'https://github.com/yangxiangmin/cicd-test.git'
            }
        }

        // 阶段 2：构建项目（使用 CMake）
        stage('Build') {
            steps {
                sh """
                    mkdir -p ${BUILD_DIR}
                    cd ${BUILD_DIR}
                    cmake .. -DCMAKE_BUILD_TYPE=Release
                    make -j4
                """
            }
        }

        // 阶段 3：运行单元测试
        stage('Test') {
            steps {
                sh """
                    cd ${BUILD_DIR}
                    ./run_tests --gtest_output="xml:${TEST_RESULTS}"
                """
                // 解析测试报告
                junit "${BUILD_DIR}/${TEST_RESULTS}"
            }
        }

        // 阶段 4：打包（生成可部署的二进制包）
        stage('Package') {
            steps {
                sh """
                    cd ${BUILD_DIR}
                    tar -czvf ${ARTIFACT_NAME} cicd_test_project
                """
                // 存档构建产物
                archiveArtifacts artifacts: "${BUILD_DIR}/${ARTIFACT_NAME}"
            }
        }

        // 阶段 5：部署到测试环境（可选）
        stage('Deploy to Staging') {
            when {
                branch 'main'  // 仅 main 分支触发
            }
            steps {
                sh "scp ${BUILD_DIR}/${ARTIFACT_NAME} user@staging-server:/opt/cicd_test_project/"
                sh "ssh user@staging-server 'tar -xzvf /opt/cicd_test_project/${ARTIFACT_NAME} -C /opt/cicd_test_project/'"
            }
        }


        // 阶段 6：部署到生产环境（手动触发）
        stage('Deploy to Production') {
            when {
                branch 'main'
                input message: 'Deploy to production?', ok: 'Yes'
            }
            steps {
                sh "scp ${BUILD_DIR}/${ARTIFACT_NAME} user@prod-server:/opt/cicd_test_project/"
                sh "ssh user@prod-server 'tar -xzvf /opt/cicd_test_project/${ARTIFACT_NAME} -C /opt/cicd_test_project/'"
                sh "ssh user@prod-server 'systemctl restart cicd_test_project.service'"
            }
        }
    }

    // 构建后操作（可选）
    post {
        success {
            slackSend channel: '#devops', message: "Build ${env.BUILD_NUMBER} succeeded!"
        }
        failure {
            slackSend channel: '#devops', message: "Build ${env.BUILD_NUMBER} failed!"
        }
    }
}